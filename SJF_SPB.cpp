#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include "Header.h"
#include "CPU.h"
#include "PCB.h"

using namespace std;

CPU sjf_spb(string args, vector<PCB*> pcbs){

	CPU runningCPU;
	deque<PCB*> readyQueue;
	int deathCount;
	float alpha;

	if(args == "spb" ) {
		string s;

		//Prompt the user for a value of alpha
		do{
			cout << "Please enter a value 0 < x <= 1 for alpha to weigh the value of the bursts: ";
			cin >> s;
			alpha = stof(s);
		}while(alpha <= 0 || alpha > 1);
	}

	while(1){
		deathCount = 0;
		//Add all processes that can be run to ready queue

		for(int i = 0; i < pcbs.size(); i++){
			
			//If the process is dead, ignore it and take note
			if(!pcbs.at(i)->getLife()){
				deathCount++;
			}
			
			//If it can be run at this point in time and is not currently in the ready queue, add it to the ready queue.
			//The ready queue should always have the first running object at the front of the queue. The order of all other elements is not set.
			else if(pcbs.at(i)->getLife() && !pcbs.at(i)->isInReady() && pcbs.at(i)->getNextRunTime() <= runningCPU.getTime()){	
				//Note that the process is in the ready queue
				pcbs.at(i)->setReadyQ();

				//Add the element to the ready queue
				readyQueue.push_back(pcbs[i]);

			}
		}

		if(args == "sjf"){
			//Find the element with the shortest runtime and put it at the front of the ready queue.
			for(int k = 1; k < readyQueue.size();k++){

				if(readyQueue.front()->getNextCPU() > readyQueue.at(k)->getNextCPU()){
					readyQueue.push_back(readyQueue.front());
					readyQueue.pop_front();
					readyQueue.push_front(*(readyQueue.begin()+k-1));
					readyQueue.erase(readyQueue.begin()+k);
				}

			}
		}
		else { //if(args == "spb")
			//Find the element with the shortest previous burst
			//Initially the SPB is unknown as there are no previous bursts, set to 1
			for(int k = 1; k < readyQueue.size();k++){

				if(readyQueue.front()->getSPB() > readyQueue.at(k)->getSPB()){
					readyQueue.push_back(readyQueue.front());
					readyQueue.pop_front();
					readyQueue.push_front(*(readyQueue.begin()+k-1));
					readyQueue.erase(readyQueue.begin()+k);
				}

			}
		}

		//If there are no living processes, stop
		if(deathCount >= pcbs.size()){
			break;
		}

		//If there are still living processes, but none of them can be run, run an idle process for one unit of time
		if(readyQueue.empty()){
			PCB* idle = new PCB();
			readyQueue.push_front(idle);
		}

		//Run the process and then remove it from the ready queue. The time alotted is as much time as the process needs to finish
		//the current CPU burst
		runningCPU.run(readyQueue.front(),readyQueue.front()->getNextCPU());
		if(args == "spb") {
			readyQueue.front()->setSPB(alpha, runningCPU.getLastRuntime());
		}
		readyQueue.pop_front();
	}
	return runningCPU;
}