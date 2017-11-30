# include <iostream>
# include <string>
# include "PuzzlePiece.h"
# include "Solution.h"
# include "Header.h"



// MAIN

int main() {

	// INPUT PARAMETERS

	int numOf_pieces = 15;
	PuzzlePiece** puzzle = new PuzzlePiece*[numOf_pieces];

	puzzle[0] = &PuzzlePiece(1, 0, 0, 1, -1);
	puzzle[1] = &PuzzlePiece(2, -1, 0, 1, 0);
	puzzle[2] = &PuzzlePiece(3, -1, 0, -1, 1);
	puzzle[3] = &PuzzlePiece(4, 1, 0, 1, 1);
	puzzle[4] = &PuzzlePiece(5, -1, 0, 0, -1);

	puzzle[5] = &PuzzlePiece(6, 0, 1, -1, 1);
	puzzle[6] = &PuzzlePiece(7, 1, 0, 0, -1);
	puzzle[7] = &PuzzlePiece(8, 0, -1, 0, -1);
	puzzle[8] = &PuzzlePiece(9, 0, -1, -1, 0);
	puzzle[9] = &PuzzlePiece(10, 1, 1, 0, 0);

	puzzle[10] = &PuzzlePiece(11, 0, -1, 0, 0);
	puzzle[11] = &PuzzlePiece(12, 0, 1, 1, 0);
	puzzle[12] = &PuzzlePiece(13, -1, 1, 1, 0);
	puzzle[13] = &PuzzlePiece(14, -1, 0, 0, 0);
	puzzle[14] = &PuzzlePiece(15, 0, 0, 0, 0);
	
	print_pieces(puzzle, numOf_pieces);

	int numOf_decomps = 4;
	Solution** decomps = new Solution*[numOf_decomps];

	decomps[0] = &(Solution(15, 1));
	decomps[1] = &(Solution(5, 3));
	decomps[2] = &(Solution(3, 5));
	decomps[3] = &(Solution(1, 15));


	solve_puzzle(puzzle, numOf_pieces, decomps, numOf_decomps);
	
	// SHOW RESULTS
	if (!is_puzzle_solved) { 
		std::cout << "this puzzle is unsolvable\n\n\n" << std::endl; 
	} else {	
		// present final_solution
		std::cout << "final_solution is: \n" << std::endl;
		print_solution(final_solution, final_height, final_width);
	}

	// FREE SOLUTION MEMORY
	free_solution(final_solution, final_height, final_width);

	// FREE PUZZLE MEMORY
	delete[] puzzle;

	// PAUSE, RETURN
	system("pause");	
	return 0;
}