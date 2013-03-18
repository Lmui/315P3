#include "PCB.h"
#include "CPU.h"
#include <iostream>
#include <vector>

using namespace std;

//Run the process for runtime units of time. runtime must be a positive number and less than or equal to the CPU burst time of the next CPU burst
//If the runtime is equal to the length of the CPU burst, removes the CPU burst from the cpuburst vector and adds ioBurst to the NextRunTime variable before popping
//ioburst. Otherwise, sets the NextRunTime variable to when the run() process finishes
void CPU::run(PCB* process, int runtime){

	//Add the process to the gantt chart data
	this->runtime.push_back(runtime);
	this->PIDs.push_back(process->getPID());
	
	//Adjust the fields within the PCB
	//Increment the timewaiting field by the length of time that the process spent between entering the ready queue and now.
	//Note that it has left the ready queue and must be readded by unsetting the readyQ flag
	process->incTWaiting(this->getTime() - process->getNextRunTime());
	process->unsetReadyQ();
	
	//Adjust ioBurst and cpuBurst dependent on runtime
	//If the runtime is insufficient to finish the current CPU burst decrement the time required to complete the cpu burst and set NextRunTime
	//to the time that the current burst finishes
	if(runtime < process->getNextCPU()){
		process->decCPUburst(runtime);
		process->incNextRunTime(runtime);
	}
	//If the runtime is sufficient to finish the current CPU burst, pop it, and set the next run time
	else{
		process->incNextRunTime(runtime + process->getNextIO());
		process->popBursts();

	}

	//Increment the CPU time by the amount of time that the current process uses
	this->time += runtime;

	//Sets the total time spent of the process to the elapsed time between when TARQ is and when the CPU burst for runtime terminates.
	process->setTTime(this->time-process->getTARQ());
}

int CPU::getTime(void){
	return this->time;
}