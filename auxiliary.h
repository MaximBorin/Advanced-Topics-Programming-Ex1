#pragma once

//This .h file contains various general helper methods which don't have anything direct to do with puzzle

#include <string>
#include <iostream>
#include <sstream>

using namespace std;


//Creates a string from an int
std::string IntToString(int num);


//A method to print errors.
void PrintMsg(string msg, ofstream* oututFile);


