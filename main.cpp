#include "main.h"


int main(int argc, char** argv)
{

		if (argc != 3)
		{
				return -1; //Expected 3 argumetns
		}


		//The path of the input file is assumed to be the first command line paramter
		string inputFilePath(argv[1]);

		//The path of the input file is assumed to be the second command line paramter
		string outputFilePath(argv[2]);


		ifstream inputFile; //The input file stream
		ofstream outputFile; //The output file stream


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
		int numElements = 0;
		PuzzlePiece** pieces = GetPuzzlePiecesFromInputFile(&inputFile, &outputFile, &numElements); //If returns, assumed that pieces are properly initialized

		if (pieces == NULL)
				return -1; //Encountered error during parsing and already printed it

		//Get statistics about the jigsaw pieces
		PuzzlePiecesStats stats = GetJigsawPiecesStats(pieces, numElements) ;

		//Validate the stats for a genearl type of puzzle (without assuming number of rows/columns)
		bool isValidPieces = IsValidJigsawPiecesStats(stats, &outputFile);

		//Attempt to solve the puzzle only if the pieces are valid
		if (isValidPieces == true)
		{
				//------------TODO------------------------

				//Parameters: pieces, numElements


				//Attempt to solve the jigsaw puzzle
				//TODO

				//If failed, print error
				//PrintMsg("Cannot solve puzzle: it seems that there is no proper solution", &outputFile);

				//If succesful, print solution
				//print_solution_to_file(final_solution, final_height, final_width, &outputFile);
		}

		delete pieces; //Delete the pieces to free pointer memory
}