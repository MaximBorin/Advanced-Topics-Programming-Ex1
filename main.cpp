#include "main.h"


int main(int argc, char** argv)
{
		//The path of the input file
		string inputfilePath = "";

		//TODO: Get file path from argv?

		//Get jigsaw pieces from the input file
		int numElements = 0;
		JigsawPiece* pieces = GetJigsawPieces(inputfilePath, &numElements); //If returns, assumed that pieces are properly initialized


		//Attempt to solve the jigsaw puzzle
		//SolveJigsawPuzzle(pieces, numElements);


		delete pieces; //Delete the pieces to free pointer memory
}