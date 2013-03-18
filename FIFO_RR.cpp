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
	if(one->getNextStart() < two->getNextStart()){
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
				if(!pcbs[i]->isInReady() && pcbs[i]->getNextStart() < runningCPU.getTime()){
					pcbs[i]->setReadyQ();
					readyQueue.push_back(pcbs[i]);
				}
			}
			//Now that all runnable processes have been added to ready queue, sort them according to when they arrived in the queue.
			//readyQueue.sort<PCB*>(compareTimes);
			runningCPU.run(readyQueue.front(),readyQueue.front()->getNextRunTime());
		}


	}

	//Run the Round Robin algorithm
	else {
	}
	return;
}