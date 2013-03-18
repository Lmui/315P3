#ifndef PCB_H_
#define PCB_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class PCB {

public:
	//Constructor
	PCB(string);

	int getPID(void);
	int getTARQ(void);
	int getTNCPU(void);
	int getPRIO(void);
	int getNextRunTime(void);
	bool isInReady(void);

	void incPRIO(int);
	void incTWaiting(int);
	void incTTime(int);
	void setReadyQ(void);
	void unsetReadyQ(void);
	
	int getNextStart(void);

private:

	//
	bool inReadyQ;
	int TNCPU;
	int PID;
	int TARQ;
	int PRIO;
	int timeWaiting;
	int totalTime;
	int nextRunTime;
	int cpuRunCount;
	vector<int> cpuBurst;
	vector<int> ioBurst;

};

#endif PCB_H_