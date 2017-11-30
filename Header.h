# define FRAME_FACTOR 2
# define NON_FRAME_FACTOR 1

# define STRAIGHT 0
# define FEMALE -1
# define MALE 1



// GLOBALS
int** final_solution;
int final_height;
int final_width;
bool is_puzzle_solved = false;


// solution methods
int how_many_decompositions(int numOf_pieces);
void initialize_decomposition_array(Solution** decomps, int numOf_pieces);
void init_solution(int** solution, int height, int width);
void init_frame(int** solution, int height, int width);
void print_solution(int** solution, int height, int width);
void print_solution_and_frame(int** solution, int height, int width);
void free_solution(int** solution, int height, int width);

// solve methods
bool puzzle_solution_dimennsion_pieces_compatibility_check(Solution decomposition, PuzzlePiece** puzzle, int numOf_pieces);
int increament_if_fit(int side, int type);
bool solve_decomp(int numOf_pieces, PuzzlePiece** puzzle, int** solution, int height, int width);
bool recursion_solve(PuzzlePiece** puzzle, int numOf_pieces, int** solution, bool* repository, int row, int column, int height, int width);
bool is_repository_exhausted(bool* repository, int numOf_pieces);
int how_many_position_fitting_pieces(int** solution, int row, int column, bool* repository, int numOf_pieces, PuzzlePiece** puzzle, int height, int width, bool* fit_array);
void next_position(int* row, int* column, int height, int width);

// puzzle methods
void print_pieces(PuzzlePiece** puzzle, int numOf_pieces);

// MAIN FUNCTION
void solve_puzzle(PuzzlePiece** puzzle, int numOf_pieces, Solution** decomps, int NumOf_decomps);



// SOLUTION METHODS

void init_solution(int** solution, int height, int width)
{
	// init non frame
	int i = 0 + NON_FRAME_FACTOR;
	int j = 0 + NON_FRAME_FACTOR;

	for (i = 1; i < height + NON_FRAME_FACTOR; i++) {
		for (j = 1; j < width + NON_FRAME_FACTOR; j++) {
			solution[i][j] = 0;
		}
	}

	// init frame
	init_frame(solution, height, width);
}

void init_frame(int** solution, int height, int width) {

	int i, j;

	for (i = 0; i < height + FRAME_FACTOR; i++) {
		for (j = 0; j < width + FRAME_FACTOR; j++) {
			if (((i == 0) || (j == 0)) || ((i == height + FRAME_FACTOR - 1) || (j == width + FRAME_FACTOR - 1))) { solution[i][j] = -1; }
		}
	}
}

void print_solution(int** solution, int height, int width) {

	int i, j;
	for (i = 1; i < height + NON_FRAME_FACTOR; i++) {
		for (j = 1; j < width + NON_FRAME_FACTOR; j++) { std::cout << solution[i][j] << " "; }
		std::cout << "\n" << std::endl;
	}
	std::cout << "\n\n" << std::endl;
}

void print_solution_and_frame(int** solution, int height, int width) {
	int i, j;
	for (i = 0; i < height + FRAME_FACTOR; i++) {
		for (j = 0; j < width + FRAME_FACTOR; j++) { std::cout << solution[i][j] << " "; }
		std::cout << "\n" << std::endl;
	}
	std::cout << "\n\n" << std::endl;
}

void free_solution(int** solution, int height, int width) {
	int i;
	for (i = 0; i < height + FRAME_FACTOR; i++) { delete[] solution[i]; }
	delete[] solution;
}


// PUZZLE METHODS

void print_pieces(PuzzlePiece** puzzle, int numOf_pieces) {
	int i;
	for (i = 0; i < numOf_pieces; i++) { puzzle[i]->printMe(); }
}


// SOLVE METHODS

bool puzzle_solution_dimennsion_pieces_compatibility_check(Solution decomposition, PuzzlePiece** puzzle, int numOf_pieces) {
	
	int height = decomposition.get_height();
	int width = decomposition.get_width();

	//left identifiers
	int num_of_left_male = 0;
	int num_of_left_female = 0;
	int num_of_left_straight = 0;

	//top identifiers
	int num_of_top_male = 0;
	int num_of_top_female = 0;
	int num_of_top_straight = 0;

	//right identiers
	int num_of_right_male = 0;
	int num_of_right_female = 0;
	int num_of_right_straight = 0;

	//bottom identifiers
	int num_of_bottom_male = 0;
	int num_of_bottom_female = 0;
	int num_of_bottom_straight = 0;

	int i;
	for (int i = 0; i < numOf_pieces; i++) {

		//left identifiers conditional increament
		num_of_left_male += increament_if_fit(puzzle[i]->left, MALE);
		num_of_left_female += increament_if_fit(puzzle[i]->left, FEMALE);
		num_of_left_straight += increament_if_fit(puzzle[i]->left, STRAIGHT);

		//top identifiers conditional increament
		num_of_top_male += increament_if_fit(puzzle[i]->top, MALE);
		num_of_top_female += increament_if_fit(puzzle[i]->top, FEMALE);
		num_of_top_straight += increament_if_fit(puzzle[i]->top, STRAIGHT);

		//right identiers conditional increament
		num_of_right_male += increament_if_fit(puzzle[i]->right, MALE);
		num_of_right_female += increament_if_fit(puzzle[i]->right, FEMALE);
		num_of_right_straight += increament_if_fit(puzzle[i]->right, STRAIGHT);

		//bottom identifiers conditional increament
		num_of_bottom_male += increament_if_fit(puzzle[i]->bottom, MALE);
		num_of_bottom_female += increament_if_fit(puzzle[i]->bottom, FEMALE);
		num_of_bottom_straight += increament_if_fit(puzzle[i]->bottom, STRAIGHT);
	}

	// piece compatibility
	if (num_of_bottom_male != num_of_top_female) { return false; }
	if (num_of_bottom_female != num_of_top_male) { return false; }
	
	if (num_of_left_male != num_of_right_female) { return false; }
	if (num_of_left_female != num_of_right_male) { return false; }

	// frame piece compatibility
	if (num_of_top_straight < width) { return false; }
	if (num_of_bottom_straight < width) { return false; }

	if (num_of_left_straight < height) { return false; }
	if (num_of_right_straight < height) { return false; }

	return true;
}

int increament_if_fit(int side, int type) {
	if (side == type) { return 1; }
	return 0;
}

bool solve_decomp(int numOf_pieces, PuzzlePiece** puzzle, int** solution, int height, int width) {

	// INITIALIZE RECURSION PARAMETERS

	// general initialization index
	int i;

	// repository initialization
	bool* repository = new bool[numOf_pieces];
	for (i = 0; i < numOf_pieces; i++) { repository[i] = true; }

	// fit_array initialization
	bool* fit_array = new bool[numOf_pieces];
	for (i = 0; i < numOf_pieces; i++) { fit_array[i] = false; }

	// position initialization
	int row = 1;
	int column = 1;

	// position_fitting_pieces initialization
	int numOf_position_fitting_pieces = how_many_position_fitting_pieces(solution, row, column, repository, numOf_pieces, puzzle, height, width, fit_array);
	int* position_fitting_pieces = new int[numOf_position_fitting_pieces];

	// if number of fitting pieces is zero, return false
	std::cout << "num of fitting pieces: " << numOf_position_fitting_pieces << "\n" << std::endl;
	if (numOf_position_fitting_pieces == 0) {
		delete[] repository;
		delete[] fit_array;
		delete[] position_fitting_pieces;

		return false;
	}

	// else - apply fitting pieces to the respective array, and try to solve after applying each to the solution in position

	// assign piece indice to fitting pieces array
	int fitting_pieces_index = 0;
	for (i = 0; i < numOf_pieces; i++) {
		if (fit_array[i]) {
			position_fitting_pieces[fitting_pieces_index] = i + 1;
			// CLARIFICATION - fit_array holds "true" for every piece index that fits
			// since for each piece: ID = index + 1, hence the i + 1 transformation
			fitting_pieces_index++;
		}
	}

	// fit array has done its job, thus freed
	delete[] fit_array;


	// ALL RECCURSION PARAMETERS SET - START THE MAGIC

	// selected piece identifier
	int position_fitting_piece;

	// try to solve with each
	for (i = 0; i < numOf_position_fitting_pieces; i++) {

		int j, k;
		// choose piece from fitting array
		position_fitting_piece = position_fitting_pieces[i];

		// create deep copy of repository
		bool* copy_repository = new bool[numOf_pieces];
		for (j = 0; j < numOf_pieces; j++) { copy_repository[j] = repository[j]; }

		// update according to piece choice
		copy_repository[position_fitting_piece - 1] = false;

		// create deep copy of solution
		int** copy_solution = new int*[height + FRAME_FACTOR];
		for (j = 0; j < height + FRAME_FACTOR; j++) {
			copy_solution[j] = new int[width + FRAME_FACTOR];
			for (k = 0; k < width + FRAME_FACTOR; k++) {
				copy_solution[j][k] = solution[j][k];
			}
		}

		// update copy_solution according to piece choice
		copy_solution[row][column] = position_fitting_piece;

		// create copy of position: row, column
		int copy_row = row;
		int copy_column = column;
		// update position copy
		next_position(&copy_row, &copy_column, height, width);

		// print solution
		print_solution(copy_solution, height, width);

		// try to solve after applying piece, and updating: position repository, solution
		bool does_piece_lead_to_puzzle_completion = recursion_solve(puzzle, numOf_pieces, copy_solution, copy_repository, copy_row, copy_column, height, width);
		// if any of the pieces leads to solution - the returned value will be "true"
		// only after all pieces are exhausted - false will be returned

		// free local copy of memory anyway
		free_solution(copy_solution, height, width);
		delete[] copy_repository;


		if (does_piece_lead_to_puzzle_completion) {
			// if the condition is fulfilled, "repository" and "position_fitting_pieces" needs be freed now.
			delete[] position_fitting_pieces;
			delete[] repository;
			return true;
		}
	}

	// only after all pieces have been tried, delete "repository" and "position_fitting_pieces", and then return false
	delete[] position_fitting_pieces;
	delete[] repository;
	return false;
}


bool recursion_solve(PuzzlePiece** puzzle, int numOf_pieces, int** solution, bool* repository, int row, int column, int height, int width) {

	if (is_repository_exhausted(repository, numOf_pieces)) {
		// if so - deep-copy solution into global final solution, and set the global "is_puzzle_solved" to "true".
		int j, k;
		final_height = height;
		final_width = width;
		final_solution = new int*[height + FRAME_FACTOR];
		for (j = 0; j < height + FRAME_FACTOR; j++) {
			final_solution[j] = new int[width + FRAME_FACTOR];
			for (k = 0; k < width + FRAME_FACTOR; k++) {
				final_solution[j][k] = solution[j][k];
			}
		}
		is_puzzle_solved = true;
	}

	if (is_puzzle_solved) {
		return true;
	}


	// general initialization index
	int i;

	// create an array of position fitting pieces

	// 1. initialize fit_array
	bool* fit_array = new bool[numOf_pieces];
	for (i = 0; i < numOf_pieces; i++) { fit_array[i] = false; }

	// 2. find how many fitting pieces
	int numOf_position_fitting_pieces = how_many_position_fitting_pieces(solution, row, column, repository, numOf_pieces, puzzle, height, width, fit_array);
	int* position_fitting_pieces = new int[numOf_position_fitting_pieces];

	// 3. if number of fitting pieces is zero, return false
	std::cout << "num of fitting pieces: " << numOf_position_fitting_pieces << "\n" << std::endl;
	if (numOf_position_fitting_pieces == 0) {

		delete[] fit_array;
		delete[] position_fitting_pieces;
		return false;
	}

	// 4. else - apply fitting pieces to the respective array, and try to solve after applying each to the solution in position

	// assign piece indice to fitting pieces array
	int fitting_pieces_index = 0;
	for (i = 0; i < numOf_pieces; i++) {
		if (fit_array[i]) {
			position_fitting_pieces[fitting_pieces_index] = i + 1;
			// CLARIFICATION - fit_array holds "true" for every piece index that fits
			// since for each piece: ID = index + 1, hence the i + 1 transformation
			fitting_pieces_index++;
		}
	}

	// 5. fit array has done its job, thus freed
	delete[] fit_array;

	// 6. ALL RECCURSION PARAMETERS SET - START THE MAGIC



	// 7. selected piece identifier
	int position_fitting_piece;

	// 8. try to solve with each
	for (i = 0; i < numOf_position_fitting_pieces; i++) {

		int j, k;
		// 8.1 choose piece from fitting array
		position_fitting_piece = position_fitting_pieces[i];

		// 8.2.1 create deep copy of repository
		bool* copy_repository = new bool[numOf_pieces];
		for (j = 0; j < numOf_pieces; j++) { copy_repository[j] = repository[j]; }

		// 8.2.2 update according to piece choice
		copy_repository[position_fitting_piece - 1] = false;

		// 8.3.1 create deep copy of solution
		int** copy_solution = new int*[height + FRAME_FACTOR];
		for (j = 0; j < height + FRAME_FACTOR; j++) {
			copy_solution[j] = new int[width + FRAME_FACTOR];
			for (k = 0; k < width + FRAME_FACTOR; k++) {
				copy_solution[j][k] = solution[j][k];
			}
		}

		// 8.3.2 update solution according to piece choice
		copy_solution[row][column] = position_fitting_piece;

		// 8.4.1 create copy of position: row, column
		int copy_row = row;
		int copy_column = column;
		// 8.4.2 update position copy
		next_position(&copy_row, &copy_column, height, width);

		// print current solution
		print_solution(copy_solution, height, width);

		// 8.5 try to solve after applying piece, and updating: position repository, solution
		bool does_piece_lead_to_puzzle_completion = recursion_solve(puzzle, numOf_pieces, copy_solution, copy_repository, copy_row, copy_column, height, width);
		// if any of the pieces leads to solution - the returned value will be "true"
		// only after all pieces are exhausted - false will be returned

		// free local copy of memory anyway
		free_solution(copy_solution, height, width);
		delete[] copy_repository;


		if (does_piece_lead_to_puzzle_completion) {
			// if the condition is fulfilled, "position_fitting_pieces" needs be freed now.
			delete[] position_fitting_pieces;
			return true;
		}
	}

	// 9. only after all pieces have been tried, delete "position_fitting_pieces", and then return false
	delete[] position_fitting_pieces;
	return false;
}

bool is_repository_exhausted(bool* repository, int numOf_pieces) {
	int i;
	for (i = 0; i < numOf_pieces; i++) {
		if (repository[i]) { return false; }
	}
	return true;
}


int how_many_position_fitting_pieces(int** solution, int row, int column, bool* repository, int numOf_pieces, PuzzlePiece** puzzle, int height, int width, bool* fit_array) {

	int res = 0;
	int i;

	for (i = 0; i < numOf_pieces; i++) //for each piece in collection
	{

		if (repository[i]) // if piece is available
		{

			bool west_fits = true;
			bool north_fits = true;
			bool east_fits = true;
			bool south_fits = true;

			//check west
			if (solution[row][column - 1] != 0) // if western slot is not free
			{
				if (solution[row][column - 1] == -1) // if western slot is frame edge
				{
					west_fits = ((puzzle[i]->left + STRAIGHT) == 0);
				}
				else
				{
					west_fits = ((puzzle[i]->left + puzzle[solution[row][column - 1] - 1]->right) == 0);
				}
			}
			//check north
			if (solution[row - 1][column] != 0) // if northern slot is not free
			{
				if (solution[row - 1][column] == -1) // if nothern slot is frame edge
				{
					north_fits = ((puzzle[i]->top + STRAIGHT) == 0);
				}
				else
				{
					north_fits = ((puzzle[i]->top + puzzle[solution[row - 1][column] - 1]->bottom) == 0);
				}
			}
			//check east
			if (solution[row][column + 1] != 0) // if eastern slot is not free
			{
				if (solution[row][column + 1] == -1) // if eastern slot is frame edge
				{
					east_fits = ((puzzle[i]->right + STRAIGHT) == 0);
				}
				else
				{
					east_fits = ((puzzle[i]->right + puzzle[solution[row][column + 1] - 1]->left) == 0);
				}
			}
			//check south
			if (solution[row + 1][column] != 0) // if shouthern slot is not free
			{
				if (solution[row + 1][column] == -1) // if southern slot is frame edge
				{
					south_fits = ((puzzle[i]->bottom + STRAIGHT) == 0);
				}
				else
				{
					south_fits = ((puzzle[i]->bottom + puzzle[solution[row + 1][column] - 1]->top) == 0);
				}
			}

			if (west_fits && north_fits && east_fits && south_fits) // if all sides fit
			{
				fit_array[puzzle[i]->ID - 1] = true;
				res += 1;
			}
		}
	}

	return res;
}


void next_position(int* row, int* column, int height, int width) {
	if (*row == height + NON_FRAME_FACTOR - 1) { *column += 1; *row = 1; }
	else { *row += 1; }
}





void solve_puzzle(PuzzlePiece** puzzle, int numOf_pieces, Solution** decomps, int numOf_decomps)
{
	int decomp_index;
	int** solution;

	// ITERATE OVER DECOMPOSITIONS
	for (decomp_index = 0; decomp_index < numOf_decomps; decomp_index++) {

		// IF ALREADY SOLVED RETURN
		if (is_puzzle_solved) {
			return;
		}

		// OTHERWISE INITIALIZE RECURSION SETTINGS
		int height = decomps[decomp_index]->get_height();
		int width = decomps[decomp_index]->get_width();

		if (puzzle_solution_dimennsion_pieces_compatibility_check(*decomps[decomp_index], puzzle, numOf_pieces) == false) { 
			std::cout << "these dimensions - height: " << height << ", width: " << width << " - are not compatible with the pieces \n\n" << std::endl;
			decomps[decomp_index]->set_compatibility(false);
			system("pause");
			continue;
		}

		int i;
		solution = new int*[height + FRAME_FACTOR];
		for (i = 0; i < height + FRAME_FACTOR; i++) {
			solution[i] = new int[width + FRAME_FACTOR];
		}
		init_solution(solution, height, width);

		// PRINT INITIAL SOLUTION WITH FRAME
		std::cout << "initial solution with frame is: \n" << std::endl;
		print_solution_and_frame(solution, height, width);

		// SOLVE PUZZLE IN CURRENT DECOMPOSITION
		solve_decomp(numOf_pieces, puzzle, solution, height, width);

		if (!is_puzzle_solved) {
			std::cout << "no solution in current decomposition - height: " << height << ", width: " << width << "\n\n" << std::endl;
		}

		// free solution
		free_solution(solution, height, width);
	}
}



int how_many_decompositions(int numOf_pieces) {

	int i;
	int how_many_decomps = 0;

	for (i = 1; i*i < numOf_pieces; i++) { if (numOf_pieces % i == 0) { how_many_decomps += 2; } }
	if (i*i == numOf_pieces) { how_many_decomps += 1; }

	return how_many_decomps;
}

void initialize_decomposition_array(Solution** decomps, int numOf_pieces) {

	int i;
	int decomp_index = 0;

	for (i = 1; i*i < numOf_pieces; i++) {
		if (numOf_pieces % i == 0) {
			decomps[decomp_index++] = new Solution(numOf_pieces / i, i);
			decomps[decomp_index++] = new Solution(i, numOf_pieces / i);
		}
	}
	if (i*i == numOf_pieces) {
		decomps[decomp_index++] = new Solution(i, i);
	}
}
