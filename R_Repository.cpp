#include "R_Repository.h"


R_Repository::R_Repository(std::vector<PuzzlePiece> puzzle_set, int numOf_pieces)
	: _numOf_pieces(numOf_pieces) 
{
	
	std::vector<PuzzlePiece> ffff_proto_vec; _sorted_puzzle_set.push_back(ffff_proto_vec);

	std::vector<PuzzlePiece> fffs_proto_vec; _sorted_puzzle_set.push_back(fffs_proto_vec);
	std::vector<PuzzlePiece> fffm_proto_vec; _sorted_puzzle_set.push_back(fffm_proto_vec);

	std::vector<PuzzlePiece> ffss_proto_vec; _sorted_puzzle_set.push_back(ffss_proto_vec);
	std::vector<PuzzlePiece> ffsm_proto_vec; _sorted_puzzle_set.push_back(ffsm_proto_vec);
	std::vector<PuzzlePiece> ffms_proto_vec; _sorted_puzzle_set.push_back(ffms_proto_vec);
	std::vector<PuzzlePiece> ffmm_proto_vec; _sorted_puzzle_set.push_back(ffmm_proto_vec);

	std::vector<PuzzlePiece> fsfs_proto_vec; _sorted_puzzle_set.push_back(fsfs_proto_vec);
	std::vector<PuzzlePiece> fsfm_proto_vec; _sorted_puzzle_set.push_back(fsfm_proto_vec);
	std::vector<PuzzlePiece> fmfm_proto_vec; _sorted_puzzle_set.push_back(fmfm_proto_vec);

	std::vector<PuzzlePiece> fsss_proto_vec; _sorted_puzzle_set.push_back(fsss_proto_vec);
	std::vector<PuzzlePiece> fssm_proto_vec; _sorted_puzzle_set.push_back(fssm_proto_vec);
	std::vector<PuzzlePiece> fsms_proto_vec; _sorted_puzzle_set.push_back(fsms_proto_vec);
	std::vector<PuzzlePiece> fsmm_proto_vec; _sorted_puzzle_set.push_back(fsmm_proto_vec);

	std::vector<PuzzlePiece> fmss_proto_vec; _sorted_puzzle_set.push_back(fmss_proto_vec);
	std::vector<PuzzlePiece> fmsm_proto_vec; _sorted_puzzle_set.push_back(fmsm_proto_vec);
	std::vector<PuzzlePiece> fmms_proto_vec; _sorted_puzzle_set.push_back(fmms_proto_vec);
	std::vector<PuzzlePiece> fmmm_proto_vec; _sorted_puzzle_set.push_back(fmmm_proto_vec);

	std::vector<PuzzlePiece> ssss_proto_vec; _sorted_puzzle_set.push_back(ssss_proto_vec);
	std::vector<PuzzlePiece> sssm_proto_vec; _sorted_puzzle_set.push_back(sssm_proto_vec);
	std::vector<PuzzlePiece> ssmm_proto_vec; _sorted_puzzle_set.push_back(ssmm_proto_vec);
	std::vector<PuzzlePiece> smsm_proto_vec; _sorted_puzzle_set.push_back(smsm_proto_vec);
	std::vector<PuzzlePiece> smmm_proto_vec; _sorted_puzzle_set.push_back(smmm_proto_vec);
	std::vector<PuzzlePiece> mmmm_proto_vec; _sorted_puzzle_set.push_back(mmmm_proto_vec);

	int proto_index;

	for (unsigned int i = 0; i < puzzle_set.size(); i++) {
		proto_index = puzzle_set[i].get_type();
		_sorted_puzzle_set[proto_index].push_back(puzzle_set[i]);
	}
}

R_Repository::~R_Repository() {
}

int R_Repository::get_numOf_pieces()
{
	return _numOf_pieces;
}

PuzzlePiece R_Repository::pop_by_prototype(int proto_index) {
	int back_piece_index = _sorted_puzzle_set[proto_index].size() - 1;
	PuzzlePiece piece = _sorted_puzzle_set[proto_index][back_piece_index];
	_sorted_puzzle_set[proto_index].pop_back();
	return piece;
}

bool R_Repository::is_empty() {
		for (unsigned int i = 0; i < _sorted_puzzle_set.size(); i++) {
		if (!_sorted_puzzle_set[i].empty()) return false;
	}
	return true;
}

std::vector<PuzzlePiece> R_Repository::get_all_unique_pieces_fitting_this_slot(R_Slot slot, bool rotatable) {

	std::vector<PuzzlePiece> fit_vector;
	int last_piece_index, rotation;
	PuzzlePiece piece;

	for (unsigned int i = 0; i < _sorted_puzzle_set.size(); i++) {
		if (!_sorted_puzzle_set[i].empty()) {
			last_piece_index = _sorted_puzzle_set[i].size() - 1;
			piece = _sorted_puzzle_set[i][last_piece_index];
			//for every unique orientation
			//	if fits the slot - push in specific orientation
			if (!rotatable) { 
				if (slot.is_piece_fit_to_slot(piece)) fit_vector.push_back(piece);
				continue;
			}
			else {
				if (slot.is_piece_fit_to_slot(piece, rotatable)) {
					// set initial orientation;
					for (rotation = 0; !(slot.is_piece_fit_to_slot(piece)); rotation += 90) {
						piece.rotate_clock_wise();
					}
					// push piece in orientation by rotational symetry factor
					int symetry_factor = piece.get_symetry_factor();
					for (rotation = 0; rotation < 360; rotation += (symetry_factor * 90)) {
						if (slot.is_piece_fit_to_slot(piece)) fit_vector.push_back(piece);
						piece.rotate_clock_wise(symetry_factor);
					}
				}
			}
		}
	}
	return fit_vector;
}