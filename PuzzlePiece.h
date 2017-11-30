#pragma once

#include "Utils.h"

#include  <algorithm>


//Defintions for the types of edge values
# define STRAIGHT 0
# define FEMALE -1
# define MALE 1

using namespace std;

//Represents one jigsaw piece
class PuzzlePiece
{
public:

	//Values of the piece's sides. -1, 0 or 1
	const int left;
	const int top;
	const int right;
	const int bottom;

	const int ID;

	PuzzlePiece(int id, int l, int t, int r, int b);
	~PuzzlePiece();
	void printMe();
};







//Checks whether the inputted value (in string format) is a valid value for a piece
bool IsValidPuzzlePieceValue(string val);

//Returns a jigsaw piece from an input line.
//If the line is in an incorrect format, the piece is returned uninitialized
PuzzlePiece* GetPuzzlePieceFromInputLine(string line);


//Get jigsaw pieces from an input file
//In case encountered an error during parsing, returns NULL
PuzzlePiece** GetPuzzlePiecesFromInputFile(ifstream* inputFile, ofstream* outputFile, int* outNumElements);