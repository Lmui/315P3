#ifndef CPU_H_
#define CPU_H_


#include "PCB.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class CPU {

	CPU(){
		this->time = 0;
	}

public:

	void run(PCB process, int runtime);


private:
	vector<int> runtime;
	vector<int> PIDs;
	int time;
};

#endif CPU_H_