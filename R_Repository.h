#pragma once
#include "PuzzlePiece.h"
#include "R_Slot.h"
#include <vector>

class R_Repository
{
public:
	R_Repository(std::vector<PuzzlePiece> puzzle_set, int numOf_pieces);

	~R_Repository();

	int get_numOf_pieces();

	PuzzlePiece pop_by_prototype(int proto_index);

	bool is_empty();

	std::vector<PuzzlePiece> get_all_unique_pieces_fitting_this_slot(R_Slot slot, bool rotatable);

	std::vector<std::vector<PuzzlePiece>> get_sorted_puzzle_set();

private:
	int _numOf_pieces;
	std::vector<std::vector<PuzzlePiece>> _sorted_puzzle_set;
};

