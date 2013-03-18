#ifndef PCB_H_
#define PCB_H_

#include <iostream>
#include <deque>
#include <string>

using namespace std;

class PCB {

public:
	//Constructor
	PCB();
	PCB(string);

	//Accessors
	int getPID(void);
	int getTARQ(void);
	int getTNCPU(void);
	int getPRIO(void);
	int getNextRunTime(void);
	int getNextCPU(void);
	int getNextIO(void);
	bool getLife(void);
	bool isInReady(void);

	//Mutators
	void incPRIO(int);
	void incTWaiting(int);
	void setTTime(int);
	void setReadyQ(void);
	void unsetReadyQ(void);
	void killProcess(void);
	void decCPUburst(int);
	void incNextRunTime(int);
	void popBursts(void);

private:

	//
	bool inReadyQ;
	bool isAlive;

	int TNCPU;
	int PID;
	int TARQ;
	int PRIO;

	//Amount of time spent waiting in the ready Queue
	int timeWaiting;

	//Amount of time since the process started executing
	int totalTime;

	//The time at which the process returns to the ready queue. Is synchronized with the time variable within a CPU. It is initialized to TARQ
	int nextRunTime;
	deque<int> cpuBurst;
	deque<int> ioBurst;

};

#endif PCB_H_