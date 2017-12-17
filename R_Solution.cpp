#include "R_Solution.h"

bool R_Solution::_is_solved = false;

R_Solution::R_Solution(R_Repository repository, int height, int width, bool rotatable)
	: _repository(repository), _height(height), _width(width), _rotatable(rotatable), _transparent_piece(0, 2, 2, 2, 2)
{
	int i, j;
	for (i = 0; i < height; i++) {
		std::vector<PuzzlePiece> temp_row;
		for (j = 0; j < width; j++) {
			temp_row.push_back(_transparent_piece);
		}
		_board.push_back(temp_row);
	}
}
R_Solution::~R_Solution() {}

// GETTERS
bool R_Solution::is_solved() { return R_Solution::_is_solved; }
int R_Solution::get_height() { return _height; }
int R_Solution::get_width() { return _width; }
std::vector<std::vector<PuzzlePiece>> R_Solution::get_board() { return _board; }
R_Repository R_Solution::get_repository() {
	return _repository;
}

// SETTERS
void R_Solution::set_solved(bool bool_set) { R_Solution::_is_solved = bool_set; }

// should remove the piece from repository, and place it on the board
void R_Solution::set_piece_in_position(PuzzlePiece piece, int row, int column) {

	_board[row].erase(_board[row].begin() + column);
	_board[row].insert(_board[row].begin() + column, piece);
	_repository.pop_by_prototype(piece.get_type());
}

// ALGORITHM STEP AND SERVICE METHODS
void R_Solution::algorithm_step(R_Solution* r_final_solution_ptr) {

	// IS SOLVED EDGE CASE
	if (_repository.is_empty()) { 
		_is_solved = true;
		*r_final_solution_ptr = *this;
		return;
	}
	if (_is_solved) { return; }

	// IF NOT - SET PARAMETERS FOR THE NEXT ALGORITHM STEP
	int row, column;
	set_min_piece_fit_position_indices(&row, &column);
	R_Position next_position(row, column, _height, _width, _board, _repository, _rotatable);
	std::vector<PuzzlePiece> fit_vector = next_position.get_fit_vector();

	// WE ARE SET - EXECUTE NEXT STEP FOR EACH OF THE 
	for each (PuzzlePiece piece in fit_vector) {
		R_Solution copy_sol(*this);
		copy_sol.set_piece_in_position(piece, row, column);
		copy_sol.algorithm_step(r_final_solution_ptr);
	}
}

void R_Solution::set_min_piece_fit_position_indices(int* row, int* column) {
	
	int i, j;
	int min_size_of_position_fit_pieces = _height * _width;
	bool slot_available;
	bool slot_adjacency_greater_than_1;

	for (i = 0; i < _height; i++) {
		for (j = 0; j < _width; j++) {

			slot_available = (_board[i][j].get_id() == 0);
			slot_adjacency_greater_than_1 = (calculate_adjacency(i, j) >= 2);

			if (slot_adjacency_greater_than_1 && slot_available) {

				R_Position temp_position(i, j, _height, _width, _board, _repository, _rotatable);
				int temp_fit_arr_size = temp_position.get_fit_array_size();

				if (temp_fit_arr_size < min_size_of_position_fit_pieces) {

					min_size_of_position_fit_pieces = temp_fit_arr_size;
					*row = i;
					*column = j;

					if (temp_fit_arr_size == 0) { return; }
				}
			}
		}
	}
}
int R_Solution::calculate_adjacency(int row, int column) {
	
	int adjacency = 0;
	if (row == 0) adjacency++;
	if (row == _height - 1) adjacency++;
	if (column == 0) adjacency++;
	if (column == _width - 1) adjacency++;
	if ((row > 0) && (_board[row - 1][column].get_id() != 0)) adjacency++;
	if ((row < _height - 1) && (_board[row + 1][column].get_id() != 0)) adjacency++;
	if ((column > 0) && (_board[row][column - 1].get_id() != 0)) adjacency++;
	if ((column < _width - 1) && (_board[row][column + 1].get_id() != 0)) adjacency++;

	return adjacency;
}

void R_Solution::print_to_file(ofstream* outputFile)
{
		if (_is_solved == false)
				return; //Can't print an unsolved puzzle

		for (int i = 0; i < _board.size(); i++)
		{
				string line("");

				for (int j = 0; j < _board[i].size(); j++)
				{
						line += IntToString(_board[i][j].get_id());

						if (_board[i][j].get_orientation() != 0)
								line += " [" + IntToString(_board[i][j].get_orientation()) + "]";

						if (j + 1 < _board[i].size())
								line += " "; //If not last element in line, add an empty space
				}

				PrintMsg(line, outputFile);
		}

}