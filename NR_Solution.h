#pragma once
#include "NR_Position.h"

class NR_Solution
{
public:
	NR_Solution(NR_Repository repository, int height, int width);
	~NR_Solution();

	// service methods
	void algorithm_step(NR_Solution* final_nr_solution_ptr);
	static bool is_solved();
	static void set_solved(bool bool_set);

	int get_height();
	int get_width();
	std::vector<std::vector<PuzzlePiece>> get_board();
	NR_Repository get_repository();
	int calculate_adjacency(int row, int column);

	void set_min_piece_fit_position_indices(int* row, int* column);
	void set_piece_in_position(int piece_id, int row, int column);


	//Prints the solution to an output file
	void print_to_file(ofstream* outputFile);


private:
	NR_Repository _repository;
	int _height;
	int _width;
	PuzzlePiece _transparent_piece;
	static bool _is_solved;
	std::vector<std::vector<PuzzlePiece>> _board;

};

