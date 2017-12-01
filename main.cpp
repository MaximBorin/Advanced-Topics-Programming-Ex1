#include "main.h"

int main(int argc, char** argv)
{
	int numElements;
	PuzzlePiece** pieces;
	ifstream inputFile; //The input file stream
	ofstream outputFile; //The output file stream
	bool isValidPieces;
	PuzzlePiecesStats stats;

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

		if (compatibility == false || !is_puzzle_solved) //If not compitable or couldn't be solved, print error
				PrintMsg("Cannot solve puzzle: it seems that there is no proper solution", &outputFile);
		
		else //If succesful, print solution
				print_solution_to_file(final_solution, final_height, final_width, &outputFile);

			// FREE SOLUTION MEMORY
			free_solution(final_solution, final_height);
	}

	// FREE PUZZLE MEMORY
	delete[] pieces;

	return 0;
}