#pragma once
#include "NR_Position.h"
#include <stack>

class NR_Solution
{
public:
	NR_Solution(NR_Repository repository, int height, int width);
	~NR_Solution();

	// service methods
	void algorithm_step(std::stack<NR_Solution>* sol_stack_ptr);
	bool is_solved();
	void set_solved(bool bool_set);

	int get_height();
	int get_width();
	std::vector<std::vector<PuzzlePiece>> get_board();
	NR_Repository get_repository();
	int calculate_adjacency(int row, int column);

	void set_min_piece_fit_position_indices(int* row, int* column);
	void set_piece_in_position(int piece_id, int row, int column);

private:
	NR_Repository _repository;
	
	int _height;
	int _width;
	bool _is_solved;
	std::vector<std::vector<PuzzlePiece>> _board;
	PuzzlePiece _transparent_piece;
};

