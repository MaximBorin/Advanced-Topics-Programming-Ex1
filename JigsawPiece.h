#pragma once

#include "auxiliary.h"

#include <fstream>
#include <string>

using namespace std;


//Enumaration for the value types a piece edge can have
enum EdgeTypeValues : int
{
		VAL_FEMALE = -1,
		VAL_STRAIGHT = 0,
		VAL_MALE = 1
};


//Represents one jigsaw piece
struct JigsawPiece
{
		//The ID of the piece
		int id;

		//Values of the piece's sides. -1, 0 or 1
		EdgeTypeValues top;
		EdgeTypeValues left;
		EdgeTypeValues right;
		EdgeTypeValues bottom;

		//If true, then this piece has been initialized with proper values.
		//Otherwise, this piece was just created and nothing was done to it
		bool isInitialized = false;
};



//Returns a jigsaw piece from an input line.
//If the line is in an incorrect format, the piece is returned uninitialized
JigsawPiece GetPieceFromInputLine(string line);


//Get jigsaw pieces from an input file
//In case encountered an error during parsing, returns NULL
JigsawPiece* GetJigsawPieces(ifstream* inputFile, ofstream* oututFile, int* outNumElements);

