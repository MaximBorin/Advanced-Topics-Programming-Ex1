#include "JigsawPiece.h"


using namespace std;

JigsawPiece GetPieceFromInputLine(string line)
{
		//TODO
		JigsawPiece piece;
		return piece;

}

JigsawPiece* GetJigsawPieces(string inputfilePath, int* outNumElements)
{
		//The input file stream
		ifstream inputFile(inputfilePath);


		if (inputFile.is_open() == false) //In case failed to open the file
		{
				cout << "Couldn't open input file " << inputfilePath;
				exit(-1);
		}


		//Get the declaration line (first line)
		string declarationLine;
		getline(inputFile, declarationLine);

		//Get the position of the "=" char in the first line
		size_t eqPos = declarationLine.find("=");

		if (eqPos == string::npos) //In case not found an "=" character or it's first char in line, therefore first line is invalid
		{
				cout << "No \"=\" char in first line of the input file " << inputfilePath;
				exit(-1);
		}

		//Get the "NumElements" substring that's expected in the first line
		string NumElementsStr = declarationLine.substr(0, eqPos);

		if (NumElementsStr != "NumElements")
		{
				cout << "Not found a \"NumElements\" in first line of input file " << inputfilePath;
				exit(-1);
		}


		//Get the integer value of the number of elements
		string NumElementsValStr = declarationLine.substr(eqPos + 1, declarationLine.length() - eqPos);
		int NumElements = std::stoi(NumElementsValStr);

		//TODO: Error handling for stoi?

		//Update the number of elements for out paramter
		*outNumElements = NumElements;


		//Load all the jigsaw pieces from file
		JigsawPiece* pieces = new JigsawPiece[NumElements];

		for (int i = 0; i < NumElements; i++)
		{
				bool isErrorInLine = false; //Set to true if encountered an error while parsing the line


																		//Read the piece's line
				string line;
				getline(inputFile, line);

				//TODO: Check if reached end of file


				//Get the piece
				JigsawPiece piece = GetPieceFromInputLine(line);

				if (piece.isInitialized == false) //In case the piece wasn't properly initialized
						isErrorInLine = true;

				if (!isErrorInLine && (piece.id <= 0 || piece.id > NumElements))
						isErrorInLine = true;


				if (!isErrorInLine && pieces[piece.id - 1].isInitialized) //If there's already a piece with the same ID in the array
						isErrorInLine = true;

				if (isErrorInLine)
				{
						cout << "Puzzle ID " << piece.id << " has wrong data : " << line;
						delete pieces;
						exit(-1);
				}

				//No error in parsing. Add the element to the array with index = ID -1
				pieces[piece.id - 1] = piece;
		}



		//TODO Check if any pieces are missing (some cells in array aren't initialized)

		return pieces;
}