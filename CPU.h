#ifndef CPU_H_
#define CPU_H_


#include "PCB.h"
#include <iostream>
#include <deque>
#include <string>

using namespace std;

class CPU {

public:
	CPU(){
		this->time = 0;
	}

	
	int getTime(void);
	int getCount(void);
	deque<int>::iterator getPID(void);
	deque<int>::iterator getRuntimes(void);
	int getLastRuntime(void);


	void run(PCB* process, int runtime);

private:
	deque<int> runtime;
	deque<int> PIDs;
	int time;
};

#endif CPU_H_