#include "auxiliary.h"

using namespace std;

void PrintMsg(string msg, ofstream* oututFile)
{
		cout << msg;
}


//Converts a number to 
std::string IntToString(int num)
{
		std::ostringstream ss;
		ss << num;
		return ss.str();
}