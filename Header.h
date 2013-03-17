#ifndef HEADER_H_
#define HEADER_H_

#include <string>
#include <iostream>

using namespace std;

void priority(string, ifstream workload);
void fifo(string, ifstream workload);
void sjf_spb(string, ifstream workload);

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

}
#endif HEADER_H_