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