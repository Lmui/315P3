#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
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

void fifo(string args, vector<PCB*> pcbs){

	//Run the first in first out algorithm
	if(args == "fifo"){
		list<PCB*> readyQueue;
		CPU runningCPU;
		while(1){
			for(int i = 0; i < pcbs.size(); i++){

				//If it can be run at this point in time and is not currently in the ready queue, add it to the ready queue.
				//The ready queue should always have the first running object at the front of the queue. The order of all other elements is not set.
				if(!pcbs[i]->isInReady() && pcbs[i]->getNextRunTime() < runningCPU.getTime()){
					
					pcbs[i]->setReadyQ();
					if(pcbs[i]->getNextRunTime() < readyQueue.front()->getNextRunTime()){
						readyQueue.push_front(pcbs[i]);
					}
					else{
						readyQueue.push_back(pcbs[i]);
					}
				}
			}

			runningCPU.run(readyQueue.front(),readyQueue.front()->getNextRunTime());

		}


	}

	//Run the Round Robin algorithm
	else {
	}
	return;
}