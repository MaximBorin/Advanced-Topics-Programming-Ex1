#include "PuzzlePiece.h"
#include <iostream>

PuzzlePiece::PuzzlePiece(int id, int l, int t, int r, int b) : ID(id), left(l), top(t), right(r), bottom(b)
{
}


PuzzlePiece::~PuzzlePiece()
{
}

void PuzzlePiece::printMe()
{
	std::cout << "piece: " << ID << " " << left << " " << top << " " << right << " " << bottom << std::endl;
	std::cout << "\n" << std::endl;
}
