#include "NR_Repository.h"


NR_Repository::NR_Repository(std::vector<PuzzlePiece> puzzle_set, int numOf_pieces)
	: _numOf_pieces(numOf_pieces), _puzzle_set(puzzle_set)
{
}


NR_Repository::~NR_Repository() {
}

NR_Repository::NR_Repository(const NR_Repository& other) {
	_numOf_pieces = other._numOf_pieces;
	_puzzle_set = other._puzzle_set;
}

int NR_Repository::get_numOf_pieces()
{
	return _numOf_pieces;
}

PuzzlePiece& NR_Repository::get_piece_by_id(int id) {
	return _puzzle_set[id - 1];
}

bool NR_Repository::is_empty() {
	int i;
	for (i = 0; i < _numOf_pieces; i++) { 
		if (_puzzle_set[i].is_available()) { return false; }
	}
	return true;
}

void NR_Repository::printMe() {
	int i;
	for (i = 0; i < _numOf_pieces; i++) {
		_puzzle_set[i].printMe();
		if (_puzzle_set[i].is_available()) std::cout << "this piece is available" << std::endl;
		else std::cout << "this piece is not available" << std::endl;
	}
}

bool NR_Repository::is_piece_available_by_id(int id) { return _puzzle_set[id - 1].is_available(); }

std::vector<PuzzlePiece> NR_Repository::get_all_unique_pieces_fitting_this_slot(NR_Slot slot) {

	int i;
	std::vector<PuzzlePiece> fit_vector;
	bool available, and_fit_to_slot, and_unique;
	
	//	push every non-duplicate available piece to fit_vector
	for (i = 0; i < _numOf_pieces; i++) {

		// set booleans to false befor respective checks
		available = and_fit_to_slot = and_unique = false;

		available = _puzzle_set[i].is_available();
		if (available) and_fit_to_slot = slot.is_piece_fit_to_slot(_puzzle_set[i]);
		if (and_fit_to_slot) and_unique = is_unique(fit_vector, _puzzle_set[i]); 

		// if available, and unique, and fit to slot..
		if (and_unique) fit_vector.push_back(_puzzle_set[i]);
	}
	return fit_vector;
}

bool NR_Repository::is_unique(std::vector<PuzzlePiece> fit_vector, PuzzlePiece piece) {
		for (unsigned int i = 0; i < fit_vector.size(); i++) {
		if (fit_vector[i] == piece) return false;
	}
	return true;
}

void NR_Repository::set_piece_unavailable_by_id(int id) {
	_puzzle_set[id - 1].set_unavailable(); 
}