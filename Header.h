#ifndef HEADER_H_
#define HEADER_H_

#include "PCB.h"
#include "CPU.h"
#include <string>
#include <iostream>

using namespace std;

CPU Algorithms(string, vector<PCB*> pcbs);
static bool compareTimes(PCB, PCB);



#endif HEADER_H_