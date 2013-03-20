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
	int getTimeWaiting(void);
	int getTotalTime(void);	
	bool shouldDie(void);
	float getSPB(void);
	int getAge(void);

	//Mutators
	void incPRIO(void);
	void incTWaiting(int);
	void setTTime(int);
	void setReadyQ(void);
	void unsetReadyQ(void);
	void killProcess(void);
	void decCPUburst(int);
	void setNextRunTime(int);
	void popBursts(void);
	void setSPB(float alpha, int burstlength);
	void incAge(void);
	void resetAge(void);
	void ageSPB(void);

private:

	//
	bool inReadyQ;
	bool isAlive;

	int TNCPU;
	int PID;
	int TARQ;
	int PRIO;

	//Should always be a positive number. Counts the number of times it was passed over
	int Age;

	//Amount of time spent waiting in the ready Queue
	int timeWaiting;
	//Amount of time since the process started executing
	int totalTime;
	//The time at which the process returns to the ready queue. Is synchronized with the time variable within a CPU. It is initialized to TARQ
	int nextRunTime;
	//The shortest previous burst
	float SPB;
	//Queues for the lengths of cpu/io bursts
	deque<int> cpuBurst;
	deque<int> ioBurst;

};

#endif PCB_H_