#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <deque>
#include "PCB.h"

using namespace std;


//Constructor
//Idle constructor
PCB::PCB(){
	this-> isAlive = true;
	this -> inReadyQ = false;
	this -> timeWaiting = 0;
	this -> totalTime = 0;
	this -> PID = -1;
	this -> TARQ = 0;
	this -> PRIO = 0;
	this -> TNCPU = 1;
	this -> cpuBurst.push_back(1);
	this -> nextRunTime = this->TARQ;
}

//Requires that the number of distinct inputs in s be at least five and that the total distinct inputs be 2*TNCPU +3
//Takes a string corresponding to one line in the text document and uses it to build a pcb object which consists of variables and two vectors with the lengths of each cpu/io burst
//All variables have defaults or are initialized via the string. 


PCB::PCB(string process){
	char* proc = new char [process.length()+1];
	strcpy(proc, process.c_str());

	this-> timeWaiting = 0;
	this-> totalTime = 0;
	this-> inReadyQ = false;
	this-> isAlive = true;

	/*
	Parse the initial arguments.
	Initializes PID, TARQ, PRIO and TNCPU to the value specified and adds all CPU/IO burst times sequentially to a vector
	named cpuBurst and ioBurst respectively
	*/
	char* tok = strtok(proc, " ");
	this->PID = stoi(tok);

	tok = strtok(NULL, " ");
	this->TARQ = stoi(tok);
	tok = strtok(NULL, " ");
	this-> PRIO = stoi(tok);
	tok = strtok(NULL, " ");
	this-> TNCPU = stoi(tok);
	tok = strtok(NULL, " ");
	this->cpuBurst.push_back(stoi(tok));
	for(int i = 0; i<TNCPU-1; i++){
		tok = strtok(NULL, " ");
		this->ioBurst.push_back(stoi(tok));
		tok = strtok(NULL, " ");
		this->cpuBurst.push_back(stoi(tok));
	}

	//Initialize the first run time to TARQ
	this->nextRunTime = this->TARQ;

}

//Accessors

//Get the process PID
int PCB::getPID(void){
	return this->PID;
}
//Get TARQ
int PCB::getTARQ(void){
	return this->TARQ;
}
//Get the number of cpubursts
int PCB::getTNCPU(void){
	return this-> TNCPU;
}
//Get the process priority
int PCB::getPRIO(void){
	return this->PRIO;
}
//Get whether or not the process is in the ready queue. Returns true if the process is in the ready queue and false otherwise
bool PCB::isInReady(void){
	return this->inReadyQ;
}
//Get the status of the process. Returns true if the process is alive or false if the process is dead.
bool PCB::getLife(void){
	return this->isAlive;
}
//Get the length of the next CPU burst
int PCB::getNextCPU(void){
	return this->cpuBurst.front();
}
//Get the length of the next IO burst, if there are no IO bursts left, return 0;
int PCB::getNextIO(void){
	if (this->ioBurst.empty()){
		return 0;
	}
	else{
		return this->ioBurst.front();
	}

}

//returns NextRunTime, the time at which the process returns to the ready queue.
int PCB::getNextRunTime(void){
	return this->nextRunTime;
}

//Mutators 

//Increment the priority of the process
void PCB::incPRIO(int){
	return;
}
//Increment the time that the process has been waiting
void PCB::incTWaiting(int time){
	this->timeWaiting += time;
	return;
}
//Set the total amount of time that this process has been running
void PCB::setTTime(int time){
	this->totalTime = time;
	return;
}
//Increment the time until the process can be run again
void PCB::incNextRunTime(int time){
	this->nextRunTime += time;
}

//Kill the process
void PCB::killProcess(void){
	this-> isAlive = false;
}

void PCB::setReadyQ(void){
	this->inReadyQ = true;
}
void PCB::unsetReadyQ(void){
	this->inReadyQ = false;
}

void PCB::decCPUburst(int time){
	this->cpuBurst.front() -= time;
}

void PCB::popBursts(void){
	this->cpuBurst.pop_front();
	if(this->ioBurst.empty()){		
		this->isAlive = false;
	}
	else{
		this->ioBurst.pop_front();
	}
}