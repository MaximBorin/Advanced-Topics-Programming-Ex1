#pragma once
#include "Repository.h"

class Position
{
public:
	Position(int row, int column, int height, int width, std::vector<std::vector<PuzzlePiece>> board, Repository repository, bool _rotatable);
	~Position();

	int get_fit_array_size();
	std::vector<PuzzlePiece> get_fit_vector();

private:
	int _row;
	int _column;
	std::vector<PuzzlePiece> _fit_vector;
	Slot slot;
};

