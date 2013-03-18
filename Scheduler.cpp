#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include "Header.h"
#include "PCB.h"
#include "CPU.h"
 
using namespace std;

int main (){

	ifstream workload;
	string filename;
	char select;
	CPU ranCPU;
	vector<PCB*> pcbs;
	int i=0;
	int turnAround = 0;
	int avgWait = 0;

	//Prompt the user for the name of the file containing the workload
	cout << "Please enter the name of the file that contains the workload: ";
	cin >> filename;
	workload.open(filename.c_str());

	
	if(workload.fail())
	{
		cout << "There was an error opening " << filename << "\n";
		system("PAUSE");
		return 0;
	}

	//As long as there is data to read from the stream, add all the data to a vector of pcbs

	while(!workload.eof()){
		string s;
		getline(workload, s);		
		pcbs.push_back(new PCB(s));
	}

	//Prompt the user to select an algorithm to analyze the data
	cout << "Please select an algorithm to analyze the data: \n" << "1. FIFO (First In First Out)\n" << "2. Round Robin with quantum time\n" 
		 << "3. Priority (Without Preemption)\n" << "4. Priority (With Preemption)\n" << "5. SJF (Shortest Job First)\n" << "6. SPB (Shortest Previous Burst)\n";

	cin >> select;

	cout << "\nChoice " << select << " selected, calculating\n\n";

	if(select == '1'){
		ranCPU = fifo("fifo", pcbs);
	}
	else if(select == '2'){
		ranCPU = fifo("RR", pcbs);
	}
	else if(select == '3'){
		ranCPU = priority("with", pcbs);
	}
	else if(select == '4'){
		ranCPU = priority("without",pcbs);
	}
	else if(select == '5'){
		ranCPU = sjf_spb("sjf", pcbs);
	}
	else if(select == '6'){
		ranCPU = sjf_spb("spb", pcbs);
	}
	else {
		cout << "Invalid choice, the program is now exiting\n";
		system("PAUSE");
		return 0;
	}	

	//Below is the code used to draw the results

	cout << "\n====================================================================\n" << "RESULTS\n";
	cout << "====================================================================\n\n";	

	int cpuTime = 0;
	deque<int>::iterator runTimes = ranCPU.getRuntimes();
	deque<int>::iterator cpuPIDs = ranCPU.getPID();	
	
	//Iterate through the list of run processes, printing their runtimes as a vertical gantt chart
	cout << "   Time Progress PID\n\n";
	for(int i = 0; i < ranCPU.getCount(); i++){
		
		cout << setw(5) << cpuTime << setw(9) << "|||||" << setw(5) << (*cpuPIDs) << "\n";
		for(int k = 1; k <(*runTimes); k++){
			cout << setw(14) << "|||||";
			cout << "\n";
		}		
		cpuTime += (*runTimes);
		runTimes++;
		cpuPIDs++;		
	}
	cout << "\n";

	//Print out the process results, PID, total waiting time and total runtime
	for(vector<PCB*>::iterator it = pcbs.begin(); it != pcbs.end(); ++it){
		turnAround += (*it)->getTotalTime();
		avgWait += (*it)->getTimeWaiting();
		cout << "Process PID is: " << (*it)->getPID() << " Total waiting time is: " << (*it)->getTimeWaiting() << " Total time running is: " << (*it)->getTotalTime();
		cout << "\n";
	}

	cout << "\n";

	//Print out the CPU utilization statistics
	cout << "The throughput is: " << fixed << setprecision(2) << ((float)ranCPU.getTime() / pcbs.size()) << " CPU time units per process on average\n";
	cout << "The waiting time is: " << fixed << setprecision(2) << ((float)avgWait / pcbs.size()) << " time units per process on average\n";
	cout << "The turnaround time is: " <<  fixed << setprecision(2) << ((float)turnAround / pcbs.size()) << " time units per process on average\n";

	cout << "\nAll processes finished execution at time " << cpuTime << "\n";
	return 0;
}