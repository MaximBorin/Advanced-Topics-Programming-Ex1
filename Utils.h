#pragma once


//This .h file contains various general utility methods which aren't strictly related to solving the puzzle

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>


using namespace std;


//Creates a string from an int
std::string IntToString(int num);


//A method to print errors.
void PrintMsg(const string& msg, ofstream* outputFile);

//Splits the provided string by the delimeter and outputs a vector contraining all the split elements
vector<string> split(const string& str, char delimeter);

//Returns true if the inputted string is a number
bool IsNumber(const string& str);
