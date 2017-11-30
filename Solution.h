#pragma once
class Solution
{
public:
	Solution(int height, int width);
	~Solution();

	int Solution::get_height();
	int Solution::get_width();
	void Solution::set_compatibility(bool bool_var);
	bool Solution::get_compatibility();

private:
	int _height;
	int _width;
	bool _compatibility;
	//int** _board;
};
