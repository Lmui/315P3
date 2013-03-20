#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include "Header.h"
#include "PCB.h"
#include "CPU.h"

using namespace std;

CPU fifo(string args, vector<PCB*> pcbs){

	CPU runningCPU;
	int quantum = 1;	
	deque<PCB*> readyQueue;	
	int deathCount;	

	if(args != "fifo"){
		string s;
		do{
			cout << "Please enter a positive integer as the time alotted to each time slice: ";
			cin >> s;
			quantum = stoi(s);
		}while(quantum < 1);
	}
	
	while(1){
		deathCount = 0;
		//Add all processes that can be run to the ready queue
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
		//Find the element with the earliest runtime and put it at the front of the ready queue.
		for(int k = 1; k < readyQueue.size();k++){
			if(readyQueue.front()->getNextRunTime() > readyQueue.at(k)->getNextRunTime()){
				readyQueue.push_front(*(readyQueue.begin()+k));
				readyQueue.erase(readyQueue.begin()+k+1);
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
		//Run the process and then remove it from the ready queue. The time alotted is either as much time as the process needs to finish
		//the current CPU burst or the time alotted by the user
		if(args == "fifo"){
			runningCPU.run(readyQueue.front(),readyQueue.front()->getNextCPU());
		}
		//Run the time slice FIFO algorithm
		else{
			if(readyQueue.front()->getNextCPU() < quantum){
				runningCPU.run(readyQueue.front(),readyQueue.front()->getNextCPU());
			}
			else{
				runningCPU.run(readyQueue.front(), quantum);
			}
		}
		readyQueue.pop_front();
	}
	return runningCPU;

}