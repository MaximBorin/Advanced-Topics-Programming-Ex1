#include "Solution.h"


Solution::Solution(int height, int width) : _height(height), _width(width)
{
	_compatibility = true;
}


Solution::~Solution()
{
}


int Solution::get_height()
{
	return _height;
}


int Solution::get_width()
{
	return _width;
}

void Solution::set_compatibility(bool bool_var)
{
	_compatibility = bool_var;
}

bool Solution::get_compatibility()
{
	return _compatibility;
}
