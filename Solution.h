#pragma once
class Solution
{
public:
	Solution(int height, int width);
	~Solution();

	int get_height();
	int get_width();
	void set_compatibility(bool bool_var);
	bool get_compatibility();

private:
	int _height;
	int _width;
	bool _compatibility;
	//int** _board;
};


