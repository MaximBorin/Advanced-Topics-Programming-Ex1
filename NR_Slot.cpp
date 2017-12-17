#include "NR_Slot.h"


NR_Slot::NR_Slot(int row, int column, std::vector<std::vector<PuzzlePiece>> board, int height, int width)
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


NR_Slot::~NR_Slot()
{
}

int NR_Slot::get_west_requirement() { return _west_requirement; }
int NR_Slot::get_north_requirement() { return _north_requirement; }
int NR_Slot::get_east_requirement() { return _east_requirement; }
int NR_Slot::get_south_requirement() { return _south_requirement; }

bool NR_Slot::is_piece_fit_to_slot(PuzzlePiece piece) {

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



void NR_Slot::print_me(int row, int column) {
	std::cout << "slot in row: " << row << ", column: " << column << std::endl;
	std::cout << "west req: " << _west_requirement;
	std::cout << " ,north req: " << _north_requirement;
	std::cout << " ,east req: " << _east_requirement;
	std::cout << " ,south req: " << _south_requirement;
	std::cout << "\n\n" << std::endl;
}
