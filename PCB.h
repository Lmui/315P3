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

	void incPRIO(int);
	int incTWaiting(int);
	int incTTime(int);

private:

	int TNCPU;
	int PID;
	int TARQ;
	int PRIO;
	int timeWaiting;
	int totalTime;
	int cpuRunCount;
	vector<int> cpuBurst;
	vector<int> ioBurst;

};

#endif PCB_H_