#include "JigsawPiece.h"


using namespace std;

JigsawPiece GetPieceFromInputLine(string line)
{
		//TODO
		JigsawPiece piece;
		return piece;

}





JigsawPiece* GetJigsawPieces(ifstream* inputFile, ofstream* oututFile, int* outNumElements)
{



		//Get the declaration line (first line)
		string declarationLine;
		getline(*inputFile, declarationLine);

		//Get the position of the "=" char in the first line
		size_t eqPos = declarationLine.find("=");

		if (eqPos == string::npos) //In case not found an "=" character or it's first char in line, therefore first line is invalid
		{
				PrintMsg("No \"=\" char in first line of the input file", oututFile);
				return NULL;
		}

		//Get the "NumElements" substring that's expected in the first line
		string NumElementsStr = declarationLine.substr(0, eqPos);

		if (NumElementsStr != "NumElements")
		{
				PrintMsg("Not found a \"NumElements\" in first line of input file.", oututFile);
				return NULL;
		}


		//Get the integer value of the number of elements
		string NumElementsValStr = declarationLine.substr(eqPos + 1, declarationLine.length() - eqPos);
		int numElements = std::stoi(NumElementsValStr);

		//TODO: Error handling for stoi?

		//Update the number of elements for out paramter
		*outNumElements = numElements;


		//Load all the jigsaw pieces from file
		JigsawPiece* pieces = new JigsawPiece[numElements];

		for (int i = 0; i < numElements; i++)
		{
				bool isErrorInLine = false; //Set to true if encountered an error while parsing the line


																		//Read the piece's line
				string line;
				getline(*inputFile, line);

				//TODO: Check if reached end of file


				//Get the piece
				JigsawPiece piece = GetPieceFromInputLine(line);

				if (piece.isInitialized == false) //In case the piece wasn't properly initialized
						isErrorInLine = true;

				if (!isErrorInLine && (piece.id <= 0 || piece.id > numElements))
						isErrorInLine = true;


				if (!isErrorInLine && pieces[piece.id - 1].isInitialized) //If there's already a piece with the same ID in the array
						isErrorInLine = true;

				if (isErrorInLine)
				{
						PrintMsg("Puzzle ID " + IntToString(piece.id) + " has wrong data : " + line, oututFile);
						delete pieces;
						exit(-1);
				}

				//No error in parsing. Add the element to the array with index = ID -1
				pieces[piece.id - 1] = piece;
		}


		//TODO Check if any pieces are missing (some cells in array aren't initialized)


		return pieces;
}

