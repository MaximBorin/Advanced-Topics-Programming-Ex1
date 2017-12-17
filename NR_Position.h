#pragma once
#include "NR_Repository.h"

class NR_Position
{
public:
	NR_Position(int row, int column, int height, int width, std::vector<std::vector<PuzzlePiece>> board, NR_Repository repository);
	~NR_Position();

	int get_fit_array_size();
	std::vector<PuzzlePiece> get_fit_vector();

private:
	NR_Slot slot;
	int _row;
	int _column;
	std::vector<PuzzlePiece> _fit_vector;
	
};

