#include "Utils.h"


using namespace std;

void PrintMsg(const string& msg, ofstream* outputFile)
{
		(*outputFile) << msg << endl;
}


//Converts a number to 
std::string IntToString(int num)
{
		std::ostringstream ss;
		ss << num;
		return ss.str();
}



vector<string> split(const string& str, char delimeter)
{
		vector<string> res; //The result string

		std::stringstream stream(str);
		std::string elem;
		while (std::getline(stream, elem, delimeter))
				res.push_back(elem);

		return res;
}


bool IsNumber(const string& str)
{
		//Returns true if the string isn't empty and all the chars are digits
		return str.empty() == false && str.find_first_not_of("0123456789") == string::npos;
}