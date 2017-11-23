#include "main.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


//Returns a jigsaw piece from an input line.
//If the line is in an incorrect format, the piece is returned uninitialized
JigsawPiece GetPieceFromInputLine(string line)
{
		//TODO
		JigsawPiece piece;
		return piece;

}


//Get jigsaw pieces form an input file
JigsawPiece* GetJigsawPieces(string inputfilePath, int* outNumElements)
{
		//The input file stream
		ifstream inputFile(inputfilePath);


		if (inputFile.is_open() == false) //In case failed to open the file
		{
				cout << "Couldn't open input file " << inputfilePath;
				exit(-1);
		}


		//Get the declaration line (first line)
		string declarationLine;
		getline(inputFile, declarationLine);

		//Get the position of the "=" char in the first line
		size_t eqPos = declarationLine.find("=");

		if (eqPos == string::npos) //In case not found an "=" character or it's first char in line, therefore first line is invalid
		{
				cout << "No \"=\" char in first line of the input file " << inputfilePath;
				exit(-1);
		}

		//Get the "NumElements" substring that's expected in the first line
		string NumElementsStr = declarationLine.substr(0, eqPos);

		if (NumElementsStr != "NumElements")
		{
				cout << "Not found a \"NumElements\" in first line of input file " << inputfilePath;
				exit(-1);
		}


		//Get the integer value of the number of elements
		string NumElementsValStr = declarationLine.substr(eqPos + 1, declarationLine.length() - eqPos);
		int NumElements = std::stoi(NumElementsValStr);

		//TODO: Error handling for stoi?

		//Update the number of elements for out paramter
		*outNumElements = NumElements;


		//Load all the jigsaw pieces from file
		JigsawPiece* pieces = new JigsawPiece[NumElements];

		for (int i = 0; i < NumElements; i++)
		{
				bool isErrorInLine = false; //Set to true if encountered an error while parsing the line


				//Read the piece's line
				string line;
				getline(inputFile, line);

				//TODO: Check if reached end of file


				//Get the piece
				JigsawPiece piece = GetPieceFromInputLine(line);

				if (piece.isInitialized == false) //In case the piece wasn't properly initialized
						isErrorInLine = true;

				if (!isErrorInLine && (piece.id <= 0 || piece.id > NumElements))
						isErrorInLine = true;


				if (!isErrorInLine && pieces[piece.id - 1].isInitialized) //If there's already a piece with the same ID in the array
						isErrorInLine = true;

				if (isErrorInLine)
				{
						cout << "Puzzle ID " << piece.id << " has wrong data : " << line;
						delete pieces;
						exit(-1);
				}

				//No error in parsing. Add the element to the array with index = ID -1
				pieces[piece.id - 1] = piece;
		}



		//TODO Check if any pieces are missing (some cells in array aren't initialized)

		return pieces;
}



//Tries to solve the jigsaw puzzle with the provided pieces
void SolveJigsawPuzzle(JigsawPiece* pieces, int numElements)
{
		//Calculate how many rows and columns the puzzle should have
		int leftStraightEdges = 0;
		int rightStraightEdges = 0;
		int topStraightEdges = 0;
		int bottomStraightEdges = 0;

		for (int i = 0; i < numElements; i++)
		{
				JigsawPiece piece = pieces[i];

				if (piece.left == 0) leftStraightEdges++;
				if (piece.right == 0) rightStraightEdges++;
				if (piece.top == 0) topStraightEdges++;
				if (piece.bottom == 0) bottomStraightEdges++;
		}

		//# of rows = # of pieces with straight left edge =   # of pieces with straight right edge
		if (leftStraightEdges != rightStraightEdges)
		{

		}

		int rows = leftStraightEdges;


		//# of columns = # of pieces with straight top edge =   # of pieces with straight bottom edge
		if (topStraightEdges != bottomStraightEdges)
		{

		}

		int columns = topStraightEdges;




		delete pieces; //Delete the pieces to free pointer memory

}



int main(int argc, char** argv)
{
		//The path of the input file
		string inputfilePath = "";

		//TODO: Get file path from argv?

		//Get jigsaw pieces from the input file
		int numElements = 0;
		JigsawPiece* pieces = GetJigsawPieces(inputfilePath, &numElements); //If returns, assumed that pieces are properly initialized


		//Attempt to solve the jigsaw puzzle
		SolveJigsawPuzzle(pieces, numElements);

}