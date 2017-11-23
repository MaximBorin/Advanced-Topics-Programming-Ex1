#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


//Represents one jigsaw piece
struct JigsawPiece
{
		//The ID of the piece
		int id;

		//Values of the piece's sides. -1, 0 or 1
		int top;
		int left;
		int right;
		int bottom;

		//If true, then this piece has been initialized with proper values.
		//Otherwise, this piece was just created and nothing was done to it
		bool isInitialized = false;
};


//Returns a jigsaw piece from an input line.
//If the line is in an incorrect format, the piece is returned uninitialized
JigsawPiece GetPieceFromInputLine(string line);


//Get jigsaw pieces form an input file
JigsawPiece* GetJigsawPieces(string inputfilePath, int* outNumElements);