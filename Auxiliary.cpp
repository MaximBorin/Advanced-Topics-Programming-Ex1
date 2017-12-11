#include "Auxiliary.h"

int how_many_decompositions(int numOf_pieces) {

	int i;
	int how_many_decomps = 0;

	for (i = 1; i*i < numOf_pieces; i++) { if (numOf_pieces % i == 0) { how_many_decomps += 2; } }
	if (i*i == numOf_pieces) { how_many_decomps += 1; }

	return how_many_decomps;
}

int how_many_decompositions(int numOf_pieces, bool rotatable) {

	if (!rotatable) { return how_many_decompositions(numOf_pieces); }
	
	int i;
	int how_many_decomps = 0;

	for (i = 1; i*i < numOf_pieces; i++) {
		if (numOf_pieces % i == 0) { 
			how_many_decomps ++;
		}
	}

	if (i*i == numOf_pieces) { how_many_decomps += 1; }

	return how_many_decomps;
}

void initialize_decomp_array(int** decomps_array, int numOf_pieces) {
	int i;
	int decomp_index = 0;

	for (i = 1; i*i < numOf_pieces; i++) {
		if (numOf_pieces % i == 0) {
			decomps_array[decomp_index][0] = i;
			decomps_array[decomp_index][1] = numOf_pieces/i;
			decomp_index++;
		}
	}

	if (i*i == numOf_pieces) {
		decomps_array[decomp_index][0] = i;
		decomps_array[decomp_index][1] = i;
	}
}