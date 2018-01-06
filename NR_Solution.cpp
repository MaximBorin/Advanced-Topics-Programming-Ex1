#include "NR_Solution.h"

NR_Solution::NR_Solution(NR_Repository repository, int height, int width)
	: _repository(repository), _height(height), _width(width), _transparent_piece(0, 2, 2, 2, 2)
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
NR_Solution::~NR_Solution() {}

// GETTERS
bool NR_Solution::is_solved() { return NR_Solution::_is_solved; }
int NR_Solution::get_height() { return _height; }
int NR_Solution::get_width() { return _width; }
std::vector<std::vector<PuzzlePiece>> NR_Solution::get_board() { return _board; }
NR_Repository NR_Solution::get_repository() {
	return _repository;
}

// SETTERS
void NR_Solution::set_solved(bool bool_set) { _is_solved = bool_set; }

void NR_Solution::set_piece_in_position(int piece_id, int row, int column) {
	//updates board and piece availability in repository
	_board[row].erase(_board[row].begin() + column);
	_board[row].insert(_board[row].begin() + column, _repository.get_piece_by_id(piece_id));
	_repository.set_piece_unavailable_by_id(piece_id);
}

// ALGORITHM STEP AND SERVICE FUNCTIONS
void NR_Solution::algorithm_step(std::stack<NR_Solution>* sol_stack_ptr) {

	// SET PARAMETERS FOR THE NEXT ALGORITHM STEP
	int row, column;
	set_min_piece_fit_position_indices(&row, &column);
	NR_Position next_position(row, column, _height, _width, _board, _repository);
	std::vector<PuzzlePiece> fit_vector = next_position.get_fit_vector();

	// WE ARE SET - EXECUTE NEXT STEP FOR EACH OF THE 
	for (unsigned i = 0; i < fit_vector.size(); i++) {
		NR_Solution copy_sol(*this);
		copy_sol.set_piece_in_position(fit_vector[i].get_id(), row, column);
		if (copy_sol.get_repository().is_empty()) copy_sol.set_solved(true);

		(*sol_stack_ptr).push(copy_sol);
	}
}

void NR_Solution::set_min_piece_fit_position_indices(int* row, int* column) {
	
	int i, j;
	int min_size_of_position_fit_pieces = _height * _width;
	bool slot_available;
	bool slot_adjacency_greater_than_1;

	for (i = 0; i < _height; i++) {
		for (j = 0; j < _width; j++) {

			slot_available = (_board[i][j].get_id() == 0);
			slot_adjacency_greater_than_1 = (calculate_adjacency(i, j) >= 2);

			if (slot_adjacency_greater_than_1 && slot_available) {

				NR_Position temp_position(i, j, _height, _width, _board, _repository);
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
int NR_Solution::calculate_adjacency(int row, int column) {
	
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