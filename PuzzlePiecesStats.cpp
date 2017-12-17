#include "PuzzlePiecesStats.h"

PuzzlePiecesStats GetJigsawPiecesStats(PuzzlePiece** pieces, int numElements)
{
		PuzzlePiecesStats stats;


		for (int i = 0; i < numElements; i++)
		{
				PuzzlePiece* piece = pieces[i];

				//Note: The value that needs to be incremented is always at index +1 compared to value of the edge
				//For example: Female side is value -1 which in the array is at index 0
				stats.rightEdges[piece->get_right() + 1]++;
				stats.leftEdges[piece->get_left() + 1]++;
				stats.topEdges[piece->get_top() + 1]++;
				stats.bottomEdges[piece->get_bottom() + 1]++;

				//Check if has pieces for the edges of the puzzle
				if (piece->get_top() == S)
				{ 
						if (piece->get_left() == S) stats.hasTL = true;
						if (piece->get_right() == S) stats.hasTR = true;
				}


				if (piece->get_bottom() == S)
				{
						if (piece->get_left() == S) stats.hasBL = true;
						if (piece->get_right() == S) stats.hasBR = true;
				}

		}

		return stats;
}


int GetEdgesCountByValType(PuzzlePiecesStats stats, EdgeTypeValueIndexes edgeValueType)
{
		return stats.rightEdges[edgeValueType] + stats.leftEdges[edgeValueType] + stats.topEdges[edgeValueType] + stats.bottomEdges[edgeValueType];
}



bool IsValidJigsawPiecesStats(PuzzlePiecesStats stats, bool rotatable, ofstream* outputFile)
{
		bool res = true;

		int straightEdges = GetEdgesCountByValType(stats, ID_STRAIGHT);
		int maleEdges = GetEdgesCountByValType(stats, ID_MALE);
		int femaleEdges = GetEdgesCountByValType(stats, ID_FEMALE);

		//A valid puzzle must have an even number of edges
		if (straightEdges % 2 == 1)
		{
				PrintMsg("Cannot solve puzzle: wrong number of straight edges", outputFile);
				res = false;
		}

		//A valid puzzle must have TL, TR, BL and BR pieces, unless it's rotatable (then it's a case-by-case chekc that's best covered during the solution)
		if (stats.hasTL == false && !rotatable)
		{
				PrintMsg("Cannot solve puzzle: missing corner element: TL", outputFile);
				res = false;
		}
		if (stats.hasTR == false && !rotatable)
		{
				PrintMsg("Cannot solve puzzle: missing corner element: TR", outputFile);
				res = false;
		}
		if (stats.hasBL == false && !rotatable)
		{
				PrintMsg("Cannot solve puzzle: missing corner element: BL", outputFile);
				res = false;
		}
		if (stats.hasBR == false && !rotatable)
		{
				PrintMsg("Cannot solve puzzle: missing corner element: BR", outputFile);
				res = false;
		}

		//A valid puzzle must have a total sum of 0 for all edges
		if (maleEdges != femaleEdges)
		{
				PrintMsg("Cannot solve puzzle: sum of edges is not zero", outputFile);
				res = false;
		}


		return res; 
}


