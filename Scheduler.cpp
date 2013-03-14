#include <iostream>
#include <fstream>
#include <string>
#include "Header.h"
 
using namespace std;

int main (){

	ifstream workload;
	string filename;
	char select;

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
	//Prompt the user to select an algorithm to analyze the data
	cout << "Please select an algorithm to analyze the data: \n" << "1. FIFO (First In First Out)\n" << "2. Round Robin with quantum time\n" 
		 << "3. Priority (Without Preemption)\n" << "4. Priority (With Preemption)\n" << "5. SJF (Shortest Job First)\n" << "6. SPB (Shortest Previous Burst)\n";

	cin >> select;
	if(select == '1'){
		fifo("fifo");
	}
	else if(select == '2'){
		fifo("RR");
	}
	else if(select == '3'){
		priority("with");
	}
	else if(select == '4'){
		priority("without");
	}
	else if(select == '5'){
		sjf_spb("sjf");
	}
	else if(select == '6'){
		sjf_spb("spb");
	}
	else {
		cout << "Invalid choice, the program is now exiting\n";
		system("PAUSE");
		return 0;
	}	
	system("PAUSE");
	return 0;
}