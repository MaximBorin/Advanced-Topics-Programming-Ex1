#pragma once

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