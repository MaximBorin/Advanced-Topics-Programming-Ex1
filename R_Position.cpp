#include "R_Position.h"

R_Position::R_Position(int row, int column, int height, int width, std::vector<std::vector<PuzzlePiece>> board, R_Repository repository, bool rotatable)
	: slot(row, column, board, height, width), _row(row), _column(column)
{
	_fit_vector = repository.get_all_unique_pieces_fitting_this_slot(slot, rotatable);
}

R_Position::~R_Position()
{
}

int R_Position::get_fit_array_size() {
	return _fit_vector.size();
}

std::vector<PuzzlePiece> R_Position::get_fit_vector() {
	return _fit_vector;
}