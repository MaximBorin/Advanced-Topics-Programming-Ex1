#pragma once
#include "Position.h"
#include "Utils.h"

class Solution
{
public:
	Solution(Repository repository, int height, int width, bool rotatable);
	~Solution();

	// service methods
	void algorithm_step();
	static bool is_solved();
	static void set_solved(bool bool_set);

	int get_height();
	int get_width();
	std::vector<std::vector<PuzzlePiece>> get_board();
	Repository get_repository();
	int calculate_adjacency(int row, int column);

	void set_min_piece_fit_position_indices(int* row, int* column);
	void set_piece_in_position(PuzzlePiece piece, int row, int column);

	//Prints the solution to an output file
	void print_to_file(ofstream* outputFile);

private:
	Repository _repository;
	
	int _height;
	int _width;
	bool _rotatable;
	static bool _is_solved;
	std::vector<std::vector<PuzzlePiece>> _board;
	PuzzlePiece _transparent_piece;
	
};




