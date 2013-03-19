#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Header.h"
#include "CPU.h"
#include "PCB.h"

using namespace std;
 
CPU priority(string args, vector<PCB*> pcbs){
	CPU runningCPU;
	deque<PCB*> readyQueue;
	int deathCount;

	if( args == "without" ) {
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
				
			//Find the element with the highest priority (lower number = higher priority) and put it at the front of the ready queue.
			for(int k = 1; k < readyQueue.size();k++){
				if(readyQueue.front()->getPRIO() > readyQueue.at(k)->getPRIO()){
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

			//Run the process and then remove it from the ready queue. The time alotted is as much time as the process needs to finish
			//the current CPU burst
			runningCPU.run(readyQueue.front(),readyQueue.front()->getNextCPU());
			readyQueue.pop_front();
		}
	}
	else if ( args == "with_pol" ) {
		cout << "Enter the time slice to be used: ";
		int time_slice = 0;
		cin >> time_slice;
		while(1) {
			deathCount = 0;
			
			// Add all processes that can be run to ready queue
			// pcbs is the vector that contains all the pcbs.
			for (int i = 0; i < pcbs.size(); i++) {
				// If the process is dead, ignore it and take note
				if(!pcbs.at(i)->getLife()) {
					deathCount++;
				} 
				// If the proces is not dead, and can be run at this point in time, and is not currently in the ready queue, add it to the ready queue
				// The ready queue should always have the first running object at the front of the queue. The order of all the other elements is not set.
				else if (pcbs.at(i)->getLife() && !pcbs.at(i)->isInReady() && pcbs.at(i)->getNextRunTime() <= runningCPU.getTime() ) {
					// Make a note that the process is in the ready queue
					pcbs.at(i)->setReadyQ();
					// Add the element to the ready queue
					readyQueue.push_back(pcbs[i]);
				}
			}

			//Find the element with the highest priority (lower number = higher priority) and put it at the front of the ready queue.
			for(int k = 1; k < readyQueue.size(); k++) {
				if(readyQueue.front()->getPRIO() > readyQueue.at(k)->getPRIO()){
					readyQueue.push_back(readyQueue.front());
					readyQueue.pop_front();
					readyQueue.push_front(*(readyQueue.begin()+k-1));
					readyQueue.erase(readyQueue.begin()+k); // erase also decrease the vector size
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

			// Run the process and then remove it from the ready queue. The time alotted is the time slice 
			// provided by the user.
			runningCPU.run(readyQueue.front(), time_slice);
			readyQueue.pop_front(); // delete first element of the ready queue. size is reduced by one
		} // end with_pol while(1)
	}
	else if ( args == "with_rude" ) {
		cout << "Priority with rude pre-emp is not being implemented yet" << endl;
	}
	return runningCPU;
}
