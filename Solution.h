#pragma once
class Solution
{
public:
	Solution(int height, int width);
	~Solution();
	int get_height();
	int Solution::get_width();

private:
	int _height;
	int _width;
	//int** _board;
};

