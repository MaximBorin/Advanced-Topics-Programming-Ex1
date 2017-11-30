#pragma once
class PuzzlePiece
{
public:

	const int left;
	const int top;
	const int right;
	const int bottom;

	const int ID;

	PuzzlePiece(int l, int t, int r, int b, int id);
	~PuzzlePiece();
	void printMe();
};