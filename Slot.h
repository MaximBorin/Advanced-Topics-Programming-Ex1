#pragma once
#include "PuzzlePiece.h"
#include <iostream>
#include <vector>

class Slot
{
public:
	Slot(int row, int column, std::vector<std::vector<PuzzlePiece>> board, int height, int width);
	~Slot();

	int get_west_requirement();
	int get_north_requirement();
	int get_east_requirement();
	int get_south_requirement();

	bool is_piece_fit_to_slot(PuzzlePiece piece, bool rotatable);

	bool is_piece_fit_to_slot(PuzzlePiece piece);

	/*void print_me(int row, int column);*/

private:
	int _west_requirement;
	int _north_requirement;
	int _east_requirement;
	int _south_requirement;
};

