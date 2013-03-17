#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Header.h"
#include "PCB.h"
 
using namespace std;

int main (){

	ifstream workload;
	string filename;
	char select;
	vector<PCB*> pcbs;
	int i=0;

	//Prompt the user for the name of the file containing the workload
	cout << "Please enter the name of the file that contains the workload: ";
	cin >> filename;
	workload.open(filename.c_str());

	//ensure the file opens correctly
	/*
	if(workload.fail())
	{
		cout << "There was an error opening " << filename << "\n";
		system("PAUSE");
		return 0;
	}
	*/

	//As long as there is data to read from the stream, add all the data to a vector of pcbs

	for(int i = 0;!workload.eof();i++){
		string s;
		getline(workload, s);
		pcbs.push_back(new PCB(s));
	}

	//Prompt the user to select an algorithm to analyze the data
	cout << "Please select an algorithm to analyze the data: \n" << "1. FIFO (First In First Out)\n" << "2. Round Robin with quantum time\n" 
		 << "3. Priority (Without Preemption)\n" << "4. Priority (With Preemption)\n" << "5. SJF (Shortest Job First)\n" << "6. SPB (Shortest Previous Burst)\n";

	cin >> select;
	if(select == '1'){
		fifo("fifo", pcbs);
	}
	else if(select == '2'){
		fifo("RR", pcbs);
	}
	else if(select == '3'){
		priority("with", pcbs);
	}
	else if(select == '4'){
		priority("without",pcbs);
	}
	else if(select == '5'){
		sjf_spb("sjf", pcbs);
	}
	else if(select == '6'){
		sjf_spb("spb", pcbs);
	}
	else {
		cout << "Invalid choice, the program is now exiting\n";
		system("PAUSE");
		return 0;
	}	
	system("PAUSE");
	return 0;
}