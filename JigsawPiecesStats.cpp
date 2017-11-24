#include "JigsawPiecesStats.h"




JigsawPiecesStats GetJigsawPiecesStats(JigsawPiece* pieces, int numElements)
{
		JigsawPiecesStats stats;


		for (int i = 0; i < numElements; i++)
		{
				JigsawPiece piece = pieces[i];

				//Note: The value that needs to be incremented is always at index +1 compared to value of the edge
				//For example: Female side is value -1 which in the array is at index 0
				stats.rightEdges[piece.right + 1]++;
				stats.leftEdges[piece.left + 1]++;
				stats.topEdges[piece.top + 1]++;
				stats.bottomEdges[piece.top + 1]++;

				//Check if has pieces for the edges of the puzzle
				if (piece.top == VAL_STRAIGHT)
				{ 
						if (piece.left == VAL_STRAIGHT) stats.hasTL;
						if (piece.right == VAL_STRAIGHT) stats.hasTR;
				}


				if (piece.bottom == VAL_STRAIGHT)
				{
						if (piece.left == VAL_STRAIGHT) stats.hasBL;
						if (piece.right == VAL_STRAIGHT) stats.hasBR;
				}

		}

		return stats;
}


int GetEdgesCountByValType(JigsawPiecesStats stats, EdgeTypeValueIndexes edgeValueType)
{
		return stats.rightEdges[edgeValueType] + stats.leftEdges[edgeValueType] + stats.topEdges[edgeValueType] + stats.bottomEdges[edgeValueType];
}



bool IsValidJigsawPiecesStats(JigsawPiecesStats stats, ofstream* oututFile)
{
		int res = true;

		int straightEdges = GetEdgesCountByValType(stats, ID_STRAIGHT);
		int maleEdges = GetEdgesCountByValType(stats, ID_MALE);
		int femaleEdges = GetEdgesCountByValType(stats, ID_FEMALE);

		//A valid puzzle must have an even number of edges
		if (straightEdges % 2 == 1)
		{
				PrintMsg("Cannot solve puzzle: wrong number of straight edges", oututFile);
				res = false;
		}

		//A valid puzzle must have TL, TR, BL and BR pieces
		if (stats.hasTL == false)
		{
				PrintMsg("Cannot solve puzzle: missing corner element: TL", oututFile);
				res = false;
		}
		if (stats.hasTR == false)
		{
				PrintMsg("Cannot solve puzzle: missing corner element: TR", oututFile);
				res = false;
		}
		if (stats.hasBL == false)
		{
				PrintMsg("Cannot solve puzzle: missing corner element: BL", oututFile);
				res = false;
		}
		if (stats.hasBR == false)
		{
				PrintMsg("Cannot solve puzzle: missing corner element: BR", oututFile);
				res = false;
		}

		//A valid puzzle must have a total sum of 0 for all edges
		if (maleEdges != femaleEdges)
		{
				PrintMsg("Cannot solve puzzle: sum of edges is not zero", oututFile);
				res = false;
		}


		return res; 
}


