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
	int ID;
	int left;
	int top;
	int right;
  int bottom;

	

	PuzzlePiece(int id, int l, int t, int r, int b);
	~PuzzlePiece();
	void printMe();
};







//Checks whether the inputted value (in string format) is a valid value for a piece
bool IsValidPuzzlePieceValue(string val);

//Returns a puzze piece from an input line.
//If the line is in an incorrect format, then NULL is returned.
//outPieceID will contain the ID of the piece (useful in case NULL is returned for the piece).
//If the ID has bad format, then return empty string npos
PuzzlePiece* GetPuzzlePieceFromInputLine(string line, string* outPieceID);


//Get jigsaw pieces from an input file
//In case encountered an error during parsing, returns NULL
PuzzlePiece** GetPuzzlePiecesFromInputFile(ifstream* inputFile, ofstream* outputFile, int* outNumElements);