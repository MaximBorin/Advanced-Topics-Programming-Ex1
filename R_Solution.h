#pragma once
#include "R_Position.h"
#include "Utils.h"
#include <stack>

class R_Solution
{
public:
	R_Solution(R_Repository repository, int height, int width, bool rotatable);
	~R_Solution();

	// service methods
	void algorithm_step(std::stack<R_Solution>* sol_stack_ptr);
	bool is_solved();
	void set_solved(bool bool_set);

	int get_height();
	int get_width();
	std::vector<std::vector<PuzzlePiece>> get_board();
	R_Repository get_repository();
	int calculate_adjacency(int row, int column);

	void set_min_piece_fit_position_indices(int* row, int* column);
	void set_piece_in_position(PuzzlePiece piece, int row, int column);

	//Prints the solution to an output file
	void print_to_file(ofstream* outputFile);

private:
	R_Repository _repository;
	
	int _height;
	int _width;
	bool _is_solved;
	std::vector<std::vector<PuzzlePiece>> _board;
	PuzzlePiece _transparent_piece;
	bool _rotatable;
};




