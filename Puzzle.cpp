#include "Puzzle.h"


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


}