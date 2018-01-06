#include "R_Slot.h"


R_Slot::R_Slot(int row, int column, std::vector<std::vector<PuzzlePiece>> board, int height, int width)
{
	// set west requirement
	if (column == 0) { _west_requirement = 0; }
	else if (board[row][column - 1].get_id() == 0) _west_requirement = 2;
	else _west_requirement = board[row][column - 1].get_right();

	// set north requirement
	if (row == 0) { _north_requirement = 0; }
	else if (board[row - 1][column].get_id() == 0) _north_requirement = 2;
	else _north_requirement = board[row - 1][column].get_bottom();

	// set east requirement
	if (column == width - 1) { _east_requirement = 0; }
	else if (board[row][column + 1].get_id() == 0) _east_requirement = 2;
	else _east_requirement = board[row][column + 1].get_left();

	// set south requirement
	if (row == height - 1) { _south_requirement = 0; }
	else if (board[row + 1][column].get_id() == 0) _south_requirement = 2;
	else _south_requirement = board[row + 1][column].get_top();
}


R_Slot::~R_Slot()
{
}

int R_Slot::get_west_requirement() { return _west_requirement; }
int R_Slot::get_north_requirement() { return _north_requirement; }
int R_Slot::get_east_requirement() { return _east_requirement; }
int R_Slot::get_south_requirement() { return _south_requirement; }

bool R_Slot::is_piece_fit_to_slot(PuzzlePiece piece, bool rotatable) {
	int rotation;
	if (rotatable) {
		for (rotation = 0; rotation < 360; rotation += 90) {
			if (this->is_piece_fit_to_slot(piece)) return true;
			piece.rotate_clock_wise();
		}
		return false;
	}
	return this->is_piece_fit_to_slot(piece);
}

bool R_Slot::is_piece_fit_to_slot(PuzzlePiece piece) {

	int piece_left = piece.get_left();
	int piece_top = piece.get_top();
	int piece_right = piece.get_right();
	int piece_bottom = piece.get_bottom();

	if ((_west_requirement != 2) && (_west_requirement + piece_left != 0)) { return false; }
	if ((_north_requirement != 2) && (_north_requirement + piece_top != 0)) { return false; }
	if ((_east_requirement != 2) && (_east_requirement + piece_right != 0)) { return false; }
	if ((_south_requirement != 2) && (_south_requirement + piece_bottom != 0)) { return false; }

	return true;
}