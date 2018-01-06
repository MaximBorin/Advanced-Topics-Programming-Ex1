#pragma once
#include "PuzzlePiece.h"
#include "NR_Slot.h"
#include <vector>

class NR_Repository
{
public:
	NR_Repository(std::vector<PuzzlePiece> puzzle_set, int numOf_pieces);

	NR_Repository(const NR_Repository& other);

	~NR_Repository();

	int get_numOf_pieces();
	PuzzlePiece& get_piece_by_id(int id);

	bool is_empty();
	bool is_piece_available_by_id(int id);

	std::vector<PuzzlePiece> get_all_unique_pieces_fitting_this_slot(NR_Slot slot);
	bool is_unique(std::vector<PuzzlePiece> fit_vector, PuzzlePiece piece);
	void set_piece_unavailable_by_id(int id);

	void printMe();

private:
	int _numOf_pieces;
	std::vector<PuzzlePiece> _puzzle_set;
};

