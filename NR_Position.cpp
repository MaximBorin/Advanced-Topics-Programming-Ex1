#include "NR_Position.h"

NR_Position::NR_Position(int row, int column, int height, int width, std::vector<std::vector<PuzzlePiece>> board, NR_Repository repository)
	: slot(row, column, board, height, width), _row(row), _column(column)
{
	_fit_vector = repository.get_all_unique_pieces_fitting_this_slot(slot);
}

NR_Position::~NR_Position()
{
}

int NR_Position::get_fit_array_size() {
	return _fit_vector.size();
}

std::vector<PuzzlePiece> NR_Position::get_fit_vector() {
	return _fit_vector;
}