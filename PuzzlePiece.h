#pragma once
#include <vector>

#define F -1
#define S 0
#define M 1
#define W 2

class PuzzlePiece
{
public:

	PuzzlePiece(int id, int left, int top, int right, int bottom);
	PuzzlePiece(int id, int left, int top, int right, int bottom, int rotational_symetry_factor);
	PuzzlePiece();
	~PuzzlePiece();
	void printMe();

	int get_id();

	int get_left();
	int get_top();
	int get_right();
	int get_bottom();

	int get_orientation();
	int get_symetry_factor();

	int get_type();
	
	void rotate_clock_wise();
	void rotate_clock_wise(int symetry_factor);

	bool is_available();
	void set_unavailable();

	void set_piece_type_and_symetry_factor();

	static std::vector<PuzzlePiece> proto_vec;

private:
	
	int _id;

	int _left;
	int _top;
	int _right;
	int _bottom;
	int _orientation;
	int _symetry_factor;
	int _type;

	bool _available;
};


bool operator== (PuzzlePiece piece1, PuzzlePiece piece2);
bool operator!= (PuzzlePiece piece1, PuzzlePiece piece2);