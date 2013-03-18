#ifndef HEADER_H_
#define HEADER_H_

#include "PCB.h"
#include <string>
#include <iostream>

using namespace std;

void priority(string,vector<PCB*> pcbs);
void fifo(string,vector<PCB*> pcbs);
void sjf_spb(string, vector<PCB*> pcbs);
static bool compareTimes(PCB, PCB);



#endif HEADER_H_