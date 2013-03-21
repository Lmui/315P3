#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include "Header.h"
#include "CPU.h"
#include "PCB.h"

using namespace std;

CPU Algorithms(string args, vector<PCB*> pcbs){

	CPU runningCPU;
	int quantum = 1;	
	deque<PCB*> readyQueue;	
	int deathCount;
	float alpha;
	int ageSpeed;	
	PCB* idle = new PCB();

	//Prompt the user for a value of quantum
	if(args == "RR" || args == "with_pol"){

		string s;		
		do{
			cout << "Please enter a positive integer as the time alotted to each time slice: ";
			cin >> s;
			quantum = stoi(s);
		}while(quantum < 1);
	}

	//Prompt the user for a value of alpha
	else if(args == "spb" ) {
		string s;
		do{
			cout << "Please enter a value 0 < x <= 1 for alpha to weigh the value of the bursts: ";
			cin >> s;
			alpha = stof(s);
		}while(alpha <= 0 || alpha > 1);
	}

	//Prompt the user for the speed of aging
	if(args != "fifo" && args != "RR"){
		string s;		
		do{
			cout << "\nPlease enter a positive integer as the speed of aging.\n\nYour choice: ";
			cin >> s;
			ageSpeed = stoi(s);
		}while(ageSpeed < 1);
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

		//Find the next process to be run and put it at the beginning of the readyqueue
		for(int k = readyQueue.size() - 1; k > 0; k--){
			if( args == "fifo" || args == "RR" ) {
				if(readyQueue.front()->getNextRunTime() > readyQueue.at(k)->getNextRunTime()){
					readyQueue.push_front(*(readyQueue.begin()+k));
					readyQueue.erase(readyQueue.begin()+k+1);
				}
			}
			else if( args == "with_rude" || args == "with_pol" || args == "without" ) {
				if(readyQueue.front()->getPRIO() > readyQueue.at(k)->getPRIO()){
					cout << runningCPU.getTime() << "priority of front is: " << readyQueue.front()->getPRIO() << " back is: " << readyQueue.at(k)->getPRIO() << "\n";
					readyQueue.push_front(*(readyQueue.begin()+k));
					readyQueue.erase(readyQueue.begin()+k+1);
				}
			} 
			else if( args == "spb" ) {
				if(readyQueue.front()->getNextCPU() > readyQueue.at(k)->getNextCPU()){
					readyQueue.push_front(*(readyQueue.begin()+k));
					readyQueue.erase(readyQueue.begin()+k+1);
				}
			}
			else { //if( args == "sjf" ) {
				if(readyQueue.front()->getNextCPU() - readyQueue.front()->getSJF_PRIO() > readyQueue.at(k)->getNextCPU() - readyQueue.at(k)->getSJF_PRIO()){
					readyQueue.push_front(*(readyQueue.begin()+k));
					readyQueue.erase(readyQueue.begin()+k+1);
				}
			}
		}

		//Age all the processes
		if(args != "fifo" && args != "RR"){
			for(int k = 1; k <readyQueue.size(); k++){
				readyQueue.at(k)->incAge();
				if(readyQueue.at(k)->getAge() == ageSpeed){
					//Run the aging mechanism
					readyQueue.at(k)->resetAge();
					if(args == "with_rude" || args == "with_pol" || args == "without"){
						//decrement the priority
						readyQueue.at(k)->incPRIO();
					}
					if(args == "spb"){
						//reduce the apparent length of the previous burst
						readyQueue.at(k)->ageSPB();
					}
					if(args == "sjf") {
						//increase the priority value for sjf
						readyQueue.at(k)->incSJF_PRIO();
					}
				}
			}
		}

		//If there are no living processes, stop
		if(deathCount >= pcbs.size()){
			break;
		}

		//If there are still living processes, but none of them can be run, run an idle process for one unit of time
		if(readyQueue.empty()){
			readyQueue.push_front(idle);
		}

		if(args == "with_rude") {
			int nextRunTime = numeric_limits<int>::max();

			// check to see the next 'happening', whether it be the next TARQ, or a process coming out of I/O burst
			// get the nearest 'happening' that is greater than current time
			for(int i = 0; i < pcbs.size(); i++){
				if( nextRunTime > pcbs[i]->getNextRunTime() && runningCPU.getTime() < pcbs[i]->getNextRunTime() ) {
					nextRunTime = pcbs[i]->getNextRunTime();
				}
			}

			// the time from now to the nearest 'happening' is how long we will run the process
			quantum = nextRunTime - runningCPU.getTime();
		}

		//Run the process and then remove it from the ready queue. The time alotted is either as much time as the process needs to finish
		//the current CPU burst or the time alotted by the user
		if(args == "fifo" || args == "without" || args == "sjf" || args == "spb"){
			runningCPU.run(readyQueue.front(),readyQueue.front()->getNextCPU());
		}
		//Run the time slice algorithm
		else { // if(args == "RR" || args == "with_rude" || args == "with_pol") {
			if(readyQueue.front()->getNextCPU() < quantum){
				runningCPU.run(readyQueue.front(),readyQueue.front()->getNextCPU());
			}
			else{
				runningCPU.run(readyQueue.front(), quantum);
			}
		}

		if(args == "spb") {
			readyQueue.front()->setSPB(alpha, runningCPU.getLastRuntime());
		}
		if(args == "with_rude" || args == "with_pol" || args == "without") {
			readyQueue.front()->resetPRIO();
		}
		readyQueue.pop_front();
	}
	delete idle;
	return runningCPU;
}