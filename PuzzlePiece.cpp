#include "PuzzlePiece.h"
#include <iostream>

PuzzlePiece::PuzzlePiece(int id, int l, int t, int r, int b)
	: _id(id), _left(l), _top(t), _right(r), _bottom(b), _orientation(0), _symetry_factor(4), _type(0), _available(true)
{
}

PuzzlePiece::PuzzlePiece(int id, int l, int t, int r, int b, int rotational_symetry_factor)
	: _id(id), _left(l), _top(t), _right(r), _bottom(b), _orientation(0), _symetry_factor(rotational_symetry_factor), _type(0), _available(true)
{
}

PuzzlePiece::PuzzlePiece() 
{
}

PuzzlePiece::~PuzzlePiece()
{
}

void PuzzlePiece::printMe()
{
	std::cout << "piece: " << _id << " " << _left << " " << _top << " " << _right << " " << _bottom << std::endl;
	if (_available) std::cout << "available"; else std::cout << "not available";
	std::cout << "\n" << std::endl;
}

bool operator== (PuzzlePiece piece1, PuzzlePiece piece2) {
	if (piece1.get_left() != piece2.get_left()) { return false; }
	if (piece1.get_top() != piece2.get_top()) { return false; }
	if (piece1.get_right() != piece2.get_right()) { return false; }
	if (piece1.get_bottom() != piece2.get_bottom()) { return false; }
	return true;
}

bool operator!= (PuzzlePiece piece1, PuzzlePiece piece2) {
	return (!(piece1 == piece2));
}

int PuzzlePiece::get_id() { return _id; }

int PuzzlePiece::get_left() { return _left; }
int PuzzlePiece::get_top() { return _top; }
int PuzzlePiece::get_right() { return _right; }
int PuzzlePiece::get_bottom() { return _bottom; }

int PuzzlePiece::get_orientation() { return _orientation; }
int PuzzlePiece::get_symetry_factor() { return _symetry_factor; }

int PuzzlePiece::get_type() { return _type; }

void PuzzlePiece::rotate_clock_wise() {
	int temp = _left;
	_left = _bottom;
	_bottom = _right;
	_right = _top;
	_top = temp;
	_orientation = (_orientation + 90) % 360;
}

void PuzzlePiece::rotate_clock_wise(int symetry_factor) {
	int i;
	for (i = 0; i < symetry_factor; i++) { (*this).rotate_clock_wise(); }
}

bool PuzzlePiece::is_available() { return _available; }

void PuzzlePiece::set_unavailable() { 
	_available = false; 
}

void PuzzlePiece::set_piece_type_and_symetry_factor() {
	std::vector<PuzzlePiece> proto_vec;
	PuzzlePiece ffff(-1, F, F, F, F, 4); PuzzlePiece fffs(-2, F, F, F, S, 1); PuzzlePiece fffm(-3, F, F, F, M, 1); 
	proto_vec.push_back(ffff); proto_vec.push_back(fffs); proto_vec.push_back(fffm);

	PuzzlePiece ffss(-4, F, F, S, S, 1); PuzzlePiece ffsm(-5, F, F, S, M, 1); PuzzlePiece ffms(-6, F, F, M, S, 1); 
	proto_vec.push_back(ffss); proto_vec.push_back(ffsm); proto_vec.push_back(ffms);

	PuzzlePiece ffmm(-7, F, F, M, M, 1); PuzzlePiece fsfs(-8, F, S, F, S, 2); PuzzlePiece fsfm(-9, F, S, F, M, 1); 
	proto_vec.push_back(ffmm); proto_vec.push_back(fsfs); proto_vec.push_back(fsfm);

	PuzzlePiece fmfm(-10, F, M, F, M, 2); PuzzlePiece fsss(-11, F, S, S, S, 1); PuzzlePiece fssm(-12, F, S, S, M, 1); 
	proto_vec.push_back(fmfm); proto_vec.push_back(fsss); proto_vec.push_back(fssm);

	PuzzlePiece fsms(-13, F, S, M, S, 1); PuzzlePiece fsmm(-14, F, S, M, M, 1); PuzzlePiece fmss(-15, F, M, S, S, 1); 
	proto_vec.push_back(fsms); proto_vec.push_back(fsmm); proto_vec.push_back(fmss);

	PuzzlePiece fmsm(-16, F, M, S, M, 1); PuzzlePiece fmms(-17, F, M, M, S, 1); PuzzlePiece fmmm(-18, F, M, M, M, 1); 
	proto_vec.push_back(fmsm); proto_vec.push_back(fmms); proto_vec.push_back(fmmm);

	PuzzlePiece ssss(-19, S, S, S, S, 4); PuzzlePiece sssm(-20, S, S, S, M, 1); PuzzlePiece ssmm(-21, S, S, M, M, 1); 
	proto_vec.push_back(ssss); proto_vec.push_back(sssm); proto_vec.push_back(ssmm);

	PuzzlePiece smsm(-22, S, M, S, M, 2); PuzzlePiece smmm(-23, S, M, M, M, 1); PuzzlePiece mmmm(-24, M, M, M, M, 4);
	proto_vec.push_back(smsm); proto_vec.push_back(smmm); proto_vec.push_back(mmmm);

	int rotation, type, symetry_factor;
	for each (PuzzlePiece proto_piece in proto_vec) {
		for (rotation = 0; rotation < 360; rotation += 90) {
			if (*this == proto_piece) {
				type = (-1 * proto_piece.get_id()) - 1;
				symetry_factor = proto_piece.get_symetry_factor();
				(*this)._type = type;
				(*this)._symetry_factor = symetry_factor;
			}
			(*this).rotate_clock_wise();
		}
	}
}

bool IsValidPuzzlePieceValue(string val)
{
		return val == "0" || val == "1" || val == "-1";
}


PuzzlePiece* GetPuzzlePieceFromInputLine(string line, string* outPieceID)
{
		//Get all elements of the piece from the line
		vector<string> inputElems = split(line, ' ');

		*outPieceID = inputElems[0]; //Put the first element (the 'ID' in output var before checking errors)

		if (inputElems.size() != 5)
				return NULL; //Wrong format. Expected five elements in a row

		if (IsNumber(inputElems[0]) == false)
				return NULL; //ID isn't a number	

										 //Confrim that each of the edges has a proper value
		for (unsigned int i = 1; i < inputElems.size(); i++)
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


		while (inputFile->eof() == false)
		{
				//Set to true if encountered an error in line
				bool isErrorInLIne = false;

				//Read the piece's line
				string line;
				getline(*inputFile, line);


				if (line.empty()) //Ignore empty lines without reporting bad format
						continue;

				//Get the piece
				string pieceIDStr;
				PuzzlePiece* piece = GetPuzzlePieceFromInputLine(line, &pieceIDStr);

				//If the piece wasn't properly initialized then line had bad format
				if (piece == NULL)
				{
						isErrorInLIne = true;

						if (IsNumber(pieceIDStr)) //If piece has numberic piece ID, then treat it as genearl erorr in line 
						{
								if (isBadLinesFormat == false)
								{
										isBadLinesFormat = true;
										badFormatLines += "Puzzle ID " + pieceIDStr + " has wrong data: " + line;
								}
								else
										badFormatLines += "\nPuzzle ID " + pieceIDStr + " has wrong data: " + line;
						}
						else //ID is not numeric. Treat it as "ID out of range" error
						{
								if (isInvalidPieceIds == false)
								{
										isInvalidPieceIds = true;
										invalidPieceIdsStr += pieceIDStr; //First ID is printed normally
								}
								else
										invalidPieceIdsStr += ", " + pieceIDStr; //Other IDs are printed in format ", <ID>"
						}
				}

				//If the piece ID is out of range
				if (piece != NULL && (piece->get_id() <= 0 || piece->get_id() > numElements))
				{
						isErrorInLIne = true;

						if (isInvalidPieceIds == false)
						{
								isInvalidPieceIds = true;
								invalidPieceIdsStr += IntToString(piece->get_id()); //First ID is printed normally
						}
						else
								invalidPieceIdsStr += ", " + IntToString(piece->get_id()); //Other IDs are printed in format ", <ID>"
				}

				//If there's already a piece with the same ID in the array (only check when ID is in valid range_
				if (piece != NULL && piece->get_id() > 0 && piece->get_id() < numElements && pieces[piece->get_id() - 1] != NULL)
				{
						isErrorInLIne = true;
						PrintMsg("The following piece ID appears more than once: " + IntToString(piece->get_id()), outputFile);
				}


				if (isErrorInLIne)
				{
						isErrorInPieces = true; //The format of the input is invalid as long as at least one line is invalid
						continue; //If there's an error in the line, skip adding it to the array
				}

				//No error in parsing. Add the element to the array with index = ID -1
				pieces[piece->get_id() - 1] = piece;
		}

		//Print lines with bad format if there are any
		if (isBadLinesFormat)
				PrintMsg(badFormatLines, outputFile);

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
								isErrorInPieces = true;
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

