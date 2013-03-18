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
		int deathCount;
		runningCPU.setProcessCount(pcbs.size());
		while(deathCount < pcbs.size()){
			deathCount = 0;
			//Add all processes to ready queue if possible
			for(int i = 0; i < pcbs.size(); i++){
				//If the process is dead, ignore it
				
				if(!pcbs[i]->getLife()){	
					deathCount++;
				}
				//If it can be run at this point in time and is not currently in the ready queue, add it to the ready queue.
				//The ready queue should always have the first running object at the front of the queue. The order of all other elements is not set.
				else if(pcbs[i]->getLife() && !pcbs[i]->isInReady() && pcbs[i]->getNextRunTime() <= runningCPU.getTime()){					
					//Note that the process is in the ready queue
					pcbs[i]->setReadyQ();

					//Add the element to the ready queue
					readyQueue.push_back(pcbs[i]);

					//Move the first arrival into the ready queue into the front of the queue
					for(int k = 1; k < readyQueue.size();k++){
						if(readyQueue.front()->getNextRunTime() > readyQueue.at(k)->getNextRunTime()){
							
							readyQueue.push_back(readyQueue.front());
							readyQueue.pop_front();
							readyQueue.push_front(*(readyQueue.begin()+k-1));
							readyQueue.erase(readyQueue.begin()+k);

						}

					}					
				}
			}
			//"Run" the first ready process
			runningCPU.run(readyQueue.front(),readyQueue.front()->getNextRunTime());

		}
		cout << "FINISHED \n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
		return runningCPU;


	}

	//Run the Round Robin algorithm
	else {
	}
	return runningCPU;
}