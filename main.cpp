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


		//The input file stream
		ifstream inputFile(inputFilePath);
		ofstream oututFile(outputFilePath);

		//TODO Check if input file exists
		/*
		if (inputFile.is_open() == false) //In case failed to open the file
		{
				PrintMsg("Couldn't open input file " + inputFilePath, &oututFile);
				return -1;
		}
		*/


		//Get jigsaw pieces from the input file
		int numElements = 0;
		JigsawPiece* pieces = GetJigsawPieces(&inputFile, &oututFile, &numElements); //If returns, assumed that pieces are properly initialized

		if (pieces == NULL)
				return -1; //Encountered error during parsing

		//Get statistics about the jigsaw pieces
		JigsawPiecesStats stats = GetJigsawPiecesStats(pieces, numElements) ;

		//Validate the stats for a genearl type of puzzle (without assuming number of rows/columns)
		bool isValidPieces = IsValidJigsawPiecesStats(stats, &oututFile);

		//Attempt to solve the puzzle only if the pieces are valid
		if (isValidPieces == true)
		{
				//Attempt to solve the jigsaw puzzle
				//SolveJigsawPuzzle(pieces, numElements);
		}

		delete pieces; //Delete the pieces to free pointer memory
}