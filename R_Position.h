#pragma once
#include "R_Repository.h"

class R_Position
{
public:
	R_Position(int row, int column, int height, int width, std::vector<std::vector<PuzzlePiece>> board, R_Repository repository, bool _rotatable);
	~R_Position();

	int get_fit_array_size();
	std::vector<PuzzlePiece> get_fit_vector();

private:
	int _row;
	int _column;
	std::vector<PuzzlePiece> _fit_vector;
	R_Slot slot;
};

