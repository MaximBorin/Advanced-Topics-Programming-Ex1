#include "Position.h"
#include "Repository.h"
#include "Solution.h"
#include "PuzzlePiece.h"
#include "Auxiliary.h"
#include <iostream>

#define TEST_MODE 30
#define RUN_MODE 40

int main() {

	int mode = TEST_MODE;
	int i = 1;

	std::vector<PuzzlePiece> puzzle_set_input;

	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 0, 0, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, 1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, -1, 1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 1, 0, 1, 1));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, 0, -1));

	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 1, -1, 1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 1, 0, 0, -1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, -1, 0, -1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, -1, -1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, 1, 1, 0, 0));

	puzzle_set_input.push_back(PuzzlePiece(i++, 0, -1, 0, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 1, 1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 1, 1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, 0, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 0, 0, 0));

	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 0, 0, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, 1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, -1, 1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 1, 0, 1, 1));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, 0, -1));

	// i = 20

	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 1, -1, 1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 1, 0, 0, -1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, -1, 0, -1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, -1, -1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, 1, 1, 0, 0));

	puzzle_set_input.push_back(PuzzlePiece(i++, 0, -1, 0, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 1, 1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 1, 1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, 0, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 0, 0, 0));

	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 0, 0, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, 1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, -1, 1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 1, 0, 1, 1));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, 0, -1));

	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 1, -1, 1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 1, 0, 0, -1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, -1, 0, -1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, -1, -1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, 1, 1, 0, 0));

	// i = 40

	puzzle_set_input.push_back(PuzzlePiece(i++, 0, -1, 0, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 1, 1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 1, 1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, 0, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 0, 0, 0));

	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 0, 0, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, 1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, -1, 1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 1, 0, 1, 1));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, 0, -1));

	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 1, -1, 1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 1, 0, 0, -1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, -1, 0, -1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, -1, -1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, 1, 1, 0, 0));

	puzzle_set_input.push_back(PuzzlePiece(i++, 0, -1, 0, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 1, 1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 1, 1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, 0, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 0, 0, 0));

	// i = 60

	/*

	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 0, 0, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, 1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, -1, 1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 1, 0, 1, 1));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, 0, -1));

	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 1, -1, 1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 1, 0, 0, -1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, -1, 0, -1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, -1, -1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, 1, 1, 0, 0));

	puzzle_set_input.push_back(PuzzlePiece(i++, 0, -1, 0, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 1, 1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 1, 1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, 0, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 0, 0, 0));

	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 0, 0, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, 1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, -1, 1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 1, 0, 1, 1));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, 0, -1));

	// i = 80

	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 1, -1, 1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 1, 0, 0, -1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, -1, 0, -1));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, -1, -1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, 1, 1, 0, 0));

	puzzle_set_input.push_back(PuzzlePiece(i++, 0, -1, 0, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 1, 1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 1, 1, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, -1, 0, 0, 0));
	puzzle_set_input.push_back(PuzzlePiece(i++, 0, 0, 0, 0));

	// i = 90

	*/
	unsigned index;
	for (index = 0; index < puzzle_set_input.size(); index++) {
		puzzle_set_input[index].set_piece_type_and_symetry_factor();
	}


	// TEST MODE

	if (mode == TEST_MODE) {

		Repository repository(puzzle_set_input, puzzle_set_input.size());

		
		int height = 10;
		int width = 6;

		Solution solution(repository, height, width, true);
		
		// check algorithm step
		solution.algorithm_step();
		
		bool is_solved = solution.is_solved();

		if (is_solved) {
			std::cout << "puzzle solved!\n\n";
		}
		

		system("pause");
		return 0;
	}

	// RUN MODE

	else  {
		/*
		// SET INPUT PARAMETERS

		int i = 0;
		

		Repository repository(puzzle_set_input, numOf_pieces);
		bool rotatable = true;

		// initialize decompositions
		int numOf_decomps = how_many_decompositions(numOf_pieces, rotatable);
		int** decomp_array = new int*[numOf_decomps];
		for (i = 0; i < numOf_decomps; i++) { decomp_array[i] = new int[2]; }
		initialize_decomp_array(decomp_array, numOf_pieces);



		// TRY TO SOLVE BY EACH DECOMPOSITION

		for (i = 0; i < numOf_decomps; i++) {
			int height = decomp_array[i][0];
			int width = decomp_array[i][1];
			Solution solution(repository, height, width, true);
			Solution::set_solved(false);

			solution.algorithm_step();
			if (Solution::is_solved()) {
				std::cout << "puzzle solved!\n\n" << std::endl;
				//print solution to file
				break;
			}
		}
		std::cout << "puzzle unsolvable\n\n" << std::endl;
		//print error to file
		system("pause");
		return 0;
		*/
	}

	//end of RUN MODE SECTION
}