#include "PCB.h"
#include "CPU.h"
#include <iostream>
#include <vector>

using namespace std;

void CPU::run(PCB* process, int runtime){
	this->runtime.push_back(runtime);
	this->PIDs.push_back(process->getPID());
	this->time += runtime;
}

int CPU::getTime(void){
	return this->time;
}