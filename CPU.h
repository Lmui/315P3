#ifndef CPU_H_
#define CPU_H_


#include "PCB.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class CPU {

public:
	CPU(){
		this->time = 0;
	}

	void run(PCB* process, int runtime);
	int getTime(void);


private:
	vector<int> runtime;
	vector<int> PIDs;
	int time;
	int totalWait;
	int totalExec;
	float avgWait;
	float throughput;
	float turnaround;
};

#endif CPU_H_