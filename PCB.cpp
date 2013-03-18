#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "PCB.h"

using namespace std;


//Constructor
PCB::PCB(string process){
	char* proc = new char [process.length()+1];
	strcpy(proc, process.c_str());

	this-> timeWaiting = 0;
	this-> totalTime = 0;
	this-> cpuRunCount = 0;
	this-> inReadyQ = false;

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

}

//Accessors
int PCB::getPID(void){
	return this->PID;
}
int PCB::getTARQ(void){
	return this->TARQ;
}
int PCB::getTNCPU(void){
	return this-> TNCPU;
}
int PCB::getPRIO(void){
	return this->PRIO;
}
bool PCB::isInReady(void){
	return this->inReadyQ;
}


//returns NextRunTime, the length of the next CPU burst
int PCB::getNextRunTime(void){
	return this->nextRunTime;
}

//Mutators (Not implemented at the moment)
void PCB::incPRIO(int){
	return;
}
void PCB::incTWaiting(int){
	return;
}
void PCB::incTTime(int){
	return;
}
void PCB::setReadyQ(void){
	this->inReadyQ = true;
}
void PCB::unsetReadyQ(void){
	this->inReadyQ = false;
}

//Other functions
//Returns the time at which the process will be finished IO bursts and returned to the ready queue.
int PCB::getNextStart(void){
	if(this->cpuRunCount == 0){
		return this->getTARQ();
	}
	else{

	}

}