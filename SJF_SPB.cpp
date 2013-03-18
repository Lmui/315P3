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

	if(args == "sjf"){
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
					cout << "Next runtime of " << pcbs.at(i)->getPID() << " is " << pcbs.at(i)->getNextRunTime() << "\n";
					//Note that the process is in the ready queue
					pcbs.at(i)->setReadyQ();

					//Add the element to the ready queue
					readyQueue.push_back(pcbs[i]);

				}
			}
			
			//Find the element with the shortest runtime and put it at the front of the ready queue.
			for(int k = 1; k < readyQueue.size();k++){
				
				if(readyQueue.front()->getNextCPU() > readyQueue.at(k)->getNextCPU()){
					readyQueue.push_back(readyQueue.front());
					readyQueue.pop_front();
					readyQueue.push_front(*(readyQueue.begin()+k-1));
					readyQueue.erase(readyQueue.begin()+k);

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
			runningCPU.run(readyQueue.front(),readyQueue.front()->getNextCPU());			
			readyQueue.pop_front();

		}

		
	}
	return runningCPU;
}