#include "PuzzlePiece.h"
#include <iostream>



using namespace std;


PuzzlePiece::PuzzlePiece(int id, int l, int t, int r, int b) : ID(id), left(l), top(t), right(r), bottom(b)
{

}


PuzzlePiece::~PuzzlePiece()
{
}

void PuzzlePiece::printMe()
{
	std::cout << "piece: " << ID << " " << left << " " << top << " " << right << " " << bottom << std::endl;
	std::cout << "\n" << std::endl;
}



bool IsValidPuzzlePieceValue(string val)
{
		return val == "0" || val == "1" || val == "-1";
}


PuzzlePiece* GetPuzzlePieceFromInputLine(string line)
{
		//Get all elements of the piece from the line
		vector<string> inputElems = split(line, ' ');

		if (inputElems.size() != 5)
				return NULL; //Wrong format. Expected five elements in a row


		if (IsNumber(inputElems[0]) == false)
				return NULL; //ID isn't a number


		//Confrim that each of the edges has a proper value
		for (int i = 1; i < inputElems.size(); i++)
				if (IsValidPuzzlePieceValue(inputElems[i]) == false)
						return NULL; //Wrong edge value
													

		int ID = stoi(inputElems[0]);
		int left = stoi(inputElems[1]);
		int top = stoi(inputElems[2]);
		int right = stoi(inputElems[3]);
		int bottom = stoi(inputElems[4]);


		PuzzlePiece* piece = new PuzzlePiece(ID, left, top, right, bottom);

		return piece;

}

PuzzlePiece** GetPuzzlePiecesFromInputFile(ifstream* inputFile, ofstream* outputFile, int* outNumElements)
{
		//Get the declaration line (first line)
		string declarationLine;
		getline(*inputFile, declarationLine);

		if (declarationLine.find("=") == string::npos) //In case not found an "=" character, first line is invalid
		{
				PrintMsg("No \"=\" char in first line of the input file", outputFile);
				return NULL;
		}

		//Get the "NumElements" substring that's expected in the first line
		//Remove white spaces first
		declarationLine.erase(remove(declarationLine.begin(), declarationLine.end(), ' '), declarationLine.end());
		vector<string> declarationElems = split(declarationLine, '=');

		if (declarationElems.size() != 2)
		{
				PrintMsg("Wrong format in first line of input file.", outputFile);
				return NULL;
		}


		if (declarationElems[0] != "NumElements")
		{
				PrintMsg("Not found a \"NumElements\" in first line of input file.", outputFile);
				return NULL;
		}


		//Validte that the number of elements is a number
		if (IsNumber(declarationElems[1]) == false)
		{
				PrintMsg("Bad format for the value of NumElements: " + declarationElems[1], outputFile);
				return NULL;
		}

		//Get the integer value of the number of elements
		int numElements = std::stoi(declarationElems[1]);

		//Update the number of elements for out paramter
		*outNumElements = numElements;


		//Load all the jigsaw pieces from file
		PuzzlePiece** pieces = new PuzzlePiece*[numElements];

		//Make sure all pointers are NULL at first
		for (int i = 0; i < numElements; i++)
				pieces[i] = NULL;


		bool isInvalidPieceIds = false; //If true, then read invalid piece IDs
		string invalidPieceIdsStr(""); //Ids of all invalid strings

		bool isBadLinesFormat = false; //If true, then has lines with bad format in the line
		string badFormatLines(""); //List of lines with bad format


		//If true, then there's some error in the pieces and need to return NULL in the end after printing errors
		bool isErrorInPieces = false;


		for (int i = 0; i < numElements; i++)
		{
				if (inputFile->eof())
						break; //Reached end of file. Can't read anymore


				//Set to true if encountered an error in line
				bool isErrorInLIne = false;

				//Read the piece's line
				string line;
				getline(*inputFile, line);


				//Get the piece
				PuzzlePiece* piece = GetPuzzlePieceFromInputLine(line);

				//If the piece wasn't properly initialized then line had bad format
				if (piece == NULL) 
				{
						isErrorInLIne = true;

						isBadLinesFormat = true;
						badFormatLines += line + "\n";
				}

				//If the piece ID is out of range
				if (piece != NULL && (piece->ID <= 0 || piece->ID > numElements))
				{
						isErrorInLIne = true;

						if (isInvalidPieceIds == false)
						{
								isInvalidPieceIds = true;
								invalidPieceIdsStr += IntToString(piece->ID); //First ID is printed normally
						}
						else
								invalidPieceIdsStr += ", " + IntToString(piece->ID); //Other IDs are printed in format ", <ID>"
				}

				//If there's already a piece with the same ID in the array (only check when ID is in valid range_
				if (piece != NULL && piece->ID > 0 && piece->ID < numElements && pieces[piece->ID - 1] != NULL)
				{
						isErrorInLIne = true;
						PrintMsg("The following piece ID appears more than once: " + IntToString(piece->ID), outputFile);
				}


				if (isErrorInLIne)
				{
						isErrorInPieces = true; //The format of the input is invalid as long as at least one line is invalid
						continue; //If there's an error in the line, skip adding it to the array
				}
						
				//No error in parsing. Add the element to the array with index = ID -1
				pieces[piece->ID - 1] = piece;
		}


		//Check if there are missing piece
		string missingPiecesIdsStr("");
		bool isPiecesMissing = false; //If true, then pieces are missing and the error message will be printed
		for (int i = 0; i < numElements; i++)
		{
				if (pieces[i] == NULL) //Not intialized piece = missing piece
				{
						if (isPiecesMissing == false)
						{
								isPiecesMissing = true;
								missingPiecesIdsStr += IntToString(i + 1); //First ID is printed normally. ID = array index +1
						}
						else
								missingPiecesIdsStr += ", " + IntToString(i + 1); //Other IDs are printed in format ", <ID>"
				}
		}

		//Print an error if there are missing pieces
		if (isPiecesMissing)
				PrintMsg("Missing puzzle element(s) with the following IDs: " + missingPiecesIdsStr, outputFile);


		//If there are pices with invalid IDs, print an error msg
		if (isInvalidPieceIds)
				PrintMsg("Puzzle of size " + IntToString(numElements) + " cannot have the following IDs: " + invalidPieceIdsStr, outputFile);


		if (isErrorInPieces)
		{
				delete pieces;
				return NULL;
		}

		return pieces;
}


