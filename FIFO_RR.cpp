#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include "Header.h"
#include "PCB.h"
#include "CPU.h"

using namespace std;


static bool compareTimes(PCB* one, PCB* two){
	if(one->getNextRunTime() < two->getNextRunTime()){
		return true;
	}
	else
		return false;
}

CPU fifo(string args, vector<PCB*> pcbs){

	CPU runningCPU;

	//Run the first in first out algorithm
	if(args == "fifo"){

		deque<PCB*> readyQueue;	
		int deathCount = 0;		
		runningCPU.setProcessCount(pcbs.size());
		while(1){
			deathCount = 0;
			//Add all processes to ready queue if possible
			for(int i = 0; i < pcbs.size(); i++){

				//If the process is dead, ignore it
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
				cout << k << " Comparing: " << readyQueue.front()->getNextRunTime() << " with: " << readyQueue.at(k)->getNextRunTime()<< "\n";
				if(readyQueue.front()->getNextRunTime() > readyQueue.at(k)->getNextRunTime()){
					cout << "Swapping the greater: " << readyQueue.front()->getNextRunTime() << " with the lesser: " << readyQueue.at(k)->getNextRunTime()<< "\n";
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
			//Remove the process from the ready queue now that it has been run.
			runningCPU.run(readyQueue.front(),readyQueue.front()->getNextCPU());
			readyQueue.pop_front();
		}
		return runningCPU;
	}

	//Run the Round Robin algorithm
	else {
	}
	return runningCPU;
}