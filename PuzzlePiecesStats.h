#pragma once

#include "PuzzlePiece.h"


//Contains statistics about jigsaw pieces
struct PuzzlePiecesStats
{
		int rightEdges[3] = {}; //CountsJigsawPiecesStats how many of the right edges are female (i=0), straight (i=1) or male (i=2)
		int leftEdges[3] = {}; //Counts how many of the left edges are female (i=0), straight (i=1) or male (i=2)
		int topEdges[3] = {}; //Counts how many of the top edges are female (i=0), straight (i=1) or male (i=2)
		int bottomEdges[3] = {}; //Counts how many of the edges sides are female (i=0), straight (i=1) or male (i=2)

		bool hasTL = false; //If true, there's a top-left piece
		bool hasTR = false; //If true, there's a top-right piece
		bool hasBL = false; //If true, there's a bottom-left piece
		bool hasBR = false; //If true, there's a bottom-right piece
};


//Enumaration for the index types of a piece edge can have in JigsawPiecesStats's arrays
//Example: rightEdges[ID_STRAIGHT] will return how many pieces have a STRAIGHT RIGHT edge
enum EdgeTypeValueIndexes : int
{
		ID_FEMALE = 0,
		ID_STRAIGHT = 1,
		ID_MALE = 2
};


//Calculates and returns statistics from the provided jigsaw pieces
//PRECONDITION: Assumes pieces are all properly intialized
PuzzlePiecesStats GetJigsawPiecesStats(PuzzlePiece** pieces, int numElements);


//Returns the total amount of edges in the puzzle which have a specific type of edge  value 
int GetEdgesCountByValType(PuzzlePiecesStats stats, EdgeTypeValueIndexes edgeValueType);


//Validates that the stats of jigsaw pieces make sense for a general jigsaw puzzle (num of rows and columns unknown)
//If False is returned, then they aren't valdi for a puzzle.
//However, even if True is returned, it does NOT mean the puzzle is necessarily solvable. We'll need to try solving it to make sure. 
bool IsValidJigsawPiecesStats(PuzzlePiecesStats stats, ofstream* outputFile);

