#include "main.h"

#define TRIAL_VERSION 10
#define REAL_VERSION 20


int main(int argc, char** argv)
{
	int version = TRIAL_VERSION;

	int numElements;
	PuzzlePiece** pieces;
	ifstream inputFile; //The input file stream
	ofstream outputFile; //The output file stream
	bool isValidPieces;
	PuzzlePiecesStats stats;

	// IF SUBMIT VERSION - GET DATA FROM FILE
	if (version == REAL_VERSION) {
		if (argc != 3)
		{
			return -1; //Expected 3 argumetns
		}


		//The path of the input file is assumed to be the first command line paramter
		string inputFilePath(argv[1]);

		//The path of the input file is assumed to be the second command line paramter
		string outputFilePath(argv[2]);


		


		try
		{
			outputFile.open(outputFilePath);
		}
		catch (std::system_error& e)
		{
			//Impossible to print exception in opening output file, because exception is suppsoed to be printed to the output file
			cerr << "Failed to open output file: " << outputFilePath << ". Exception: " << e.code().message();
			return -1;
		}

		try
		{
			inputFile.open(inputFilePath);
		}
		catch (std::system_error& e)
		{
			PrintMsg("Failed to open input file: " + inputFilePath + ". Exception: " + e.code().message(), &outputFile);
			return -1;
		}


		//Get jigsaw pieces from the input file
		numElements = 0;
		pieces = GetPuzzlePiecesFromInputFile(&inputFile, &outputFile, &numElements); //If returns, assumed that pieces are properly initialized

		if (pieces == NULL)
			return -1; //Encountered error during parsing and already printed it

					   //Get statistics about the jigsaw pieces
		stats = GetJigsawPiecesStats(pieces, numElements);

		//Validate the stats for a genearl type of puzzle (without assuming number of rows/columns)
		isValidPieces = IsValidJigsawPiecesStats(stats, &outputFile);
	}

	// OTHERWISE - USE THIS DEFAULT DATA SET
	else {
	numElements = 15;
	pieces = new PuzzlePiece*[numElements];

	pieces[0] = &PuzzlePiece(1, 0, 0, 1, -1);
	pieces[1] = &PuzzlePiece(2, -1, 0, 1, 0);
	pieces[2] = &PuzzlePiece(3, -1, 0, -1, 1);
	pieces[3] = &PuzzlePiece(4, 1, 0, 1, 1);
	pieces[4] = &PuzzlePiece(5, -1, 0, 0, -1);

	pieces[5] = &PuzzlePiece(6, 0, 1, -1, 1);
	pieces[6] = &PuzzlePiece(7, 1, 0, 0, -1);
	pieces[7] = &PuzzlePiece(8, 0, -1, 0, -1);
	pieces[8] = &PuzzlePiece(9, 0, -1, -1, 0);
	pieces[9] = &PuzzlePiece(10, 1, 1, 0, 0);

	pieces[10] = &PuzzlePiece(11, 0, -1, 0, 0);
	pieces[11] = &PuzzlePiece(12, 0, 1, 1, 0);
	pieces[12] = &PuzzlePiece(13, -1, 1, 1, 0);
	pieces[13] = &PuzzlePiece(14, -1, 0, 0, 0);
	pieces[14] = &PuzzlePiece(15, 0, 0, 0, 0);

	isValidPieces = true;
	}

	//Attempt to solve the puzzle only if the pieces are valid
	if (isValidPieces == true)
	{
		//Parameters: pieces, numElements
		int numOf_decomps = how_many_decompositions(numElements);
		Solution** decomps = new Solution*[numOf_decomps];
		initialize_decomposition_array(decomps, numElements);

		//Attempt to solve the jigsaw puzzle
		solve_puzzle(pieces, numElements, decomps, numOf_decomps);

		//If neither of the solution decompositions fit the puzzle set (I.E - num_of straight top did not fit any decomposition etc..)
		bool compatibility = check_decompositions_puzzleSet_compatibility(decomps, numOf_decomps);
		if (compatibility == false) {
			
			//TO DO - SHOULD THIS CHECK UP BE HERE? OR SHOULD IT BE DONE NEXT TO THE PUZZLE SET STATS VALIDATION?
			PrintMsg("Neither of the possible rectangular solution dimensions fit the puzzle set", &outputFile);
		}

		//TO DO - IF THE COMPATIBILITY CHECK FAILED - "THE CANNOT SOLVE PUZZLE" MESSAGE SHOULD BE AVOIDED
		//==> HENCE THE "else" BEFORE CHECKING "is_puzzle_solved" int the next line:
		else

		//If failed, print error
		if (!is_puzzle_solved) {

			// IF SUBMIT VERSION - WRITE ERROR MESSAGE TO FILE, OTHERWISE - PRINT TO SCREEN
			if (version == REAL_VERSION) {
				PrintMsg("Cannot solve puzzle: it seems that there is no proper solution", &outputFile);
			} else {
				std::cout << "this puzzle is unsolvable\n\n\n" << std::endl;
			}

		//If succesful, print solution
		} else {

			// IF SUBMIT VERSION - WRITE SOLUTION TO FILE, OTHERWISE - PRINT TO SCREEN
			if (version == REAL_VERSION) {
				print_solution_to_file(final_solution, final_height, final_width, &outputFile);
			} else {
				std::cout << "final_solution is: \n" << std::endl;
			}

			// FREE SOLUTION MEMORY
			free_solution(final_solution, final_height, final_width);
		}

		// FREE PUZZLE MEMORY
		delete[] pieces;

		// PAUSE, RETURN
		std::system("pause");
		return 0;
	}
	delete pieces; //Delete the pieces to free pointer memory
}