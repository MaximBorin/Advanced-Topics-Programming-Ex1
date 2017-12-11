#pragma once
#include "PuzzlePiece.h"
#include "Slot.h"
#include <vector>

class Repository
{
public:
	Repository(std::vector<PuzzlePiece> puzzle_set, int numOf_pieces);

	~Repository();

	int get_numOf_pieces();

	PuzzlePiece pop_by_prototype(int proto_index);

	bool is_empty();

	std::vector<PuzzlePiece> get_all_unique_pieces_fitting_this_slot(Slot slot, bool rotatable);

	/*
	bool is_unique(std::vector<PuzzlePiece> fit_vector, PuzzlePiece piece);
	void set_piece_unavailable_by_id(int id);

	void printMe();
	*/

private:
	int _numOf_pieces;
	std::vector<std::vector<PuzzlePiece>> _sorted_puzzle_set;

	/*
	PuzzlePiece ffff;

	PuzzlePiece fffs;
	PuzzlePiece fffm;

	PuzzlePiece ffss;
	PuzzlePiece ffsm;
	PuzzlePiece ffms;
	PuzzlePiece ffmm;

	PuzzlePiece fsfs;
	PuzzlePiece fsfm;
	PuzzlePiece fmfm;

	PuzzlePiece fsss;
	PuzzlePiece fssm;
	PuzzlePiece fsms;
	PuzzlePiece fsmm;

	PuzzlePiece fmss;
	PuzzlePiece fmsm;
	PuzzlePiece fmms;
	PuzzlePiece fmmm;

	PuzzlePiece ssss;
	PuzzlePiece sssm;
	PuzzlePiece ssmm;
	PuzzlePiece smsm;
	PuzzlePiece smmm;
	PuzzlePiece mmmm;

	std::vector<PuzzlePiece> prototype_vec;
	*/
};

