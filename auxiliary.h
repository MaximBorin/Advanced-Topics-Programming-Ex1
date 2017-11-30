#pragma once

#include "PuzzlePiece.h"
#include "Solution.h"
#include  "Utils.h"

# define FRAME_FACTOR 2
# define NON_FRAME_FACTOR 1


// GLOBALS
static int** final_solution;
static int final_height;
static int final_width;
static bool is_puzzle_solved = false;



// solution methods
int how_many_decompositions(int numOf_pieces);
void initialize_decomposition_array(Solution** decomps, int numOf_pieces);
void init_solution(int** solution, int height, int width);
void init_frame(int** solution, int height, int width);
void print_solution(int** solution, int height, int width);
void print_solution_and_frame(int** solution, int height, int width);
void print_solution_to_file(int** solution, int height, int width, ofstream* outputFile);
void free_solution(int** solution, int height, int width);

// solve methods
bool puzzle_solution_dimennsion_pieces_compatibility_check(Solution decomposition, PuzzlePiece** puzzle, int numOf_pieces);
int increament_if_fit(int side, int type);
bool solve_decomp(int numOf_pieces, PuzzlePiece** puzzle, int** solution, int height, int width);
bool recursion_solve(PuzzlePiece** puzzle, int numOf_pieces, int** solution, bool* repository, int row, int column, int height, int width);
bool is_repository_exhausted(bool* repository, int numOf_pieces);
int how_many_position_fitting_pieces(int** solution, int row, int column, bool* repository, int numOf_pieces, PuzzlePiece** puzzle, int height, int width, bool* fit_array);
void next_position(int* row, int* column, int height, int width);

// puzzle methods
void print_pieces(PuzzlePiece** puzzle, int numOf_pieces);

// MAIN FUNCTION
void solve_puzzle(PuzzlePiece** puzzle, int numOf_pieces, Solution** decomps, int NumOf_decomps);