#include "main.h"

// thread adjustment
#include <stack>
#include <mutex>
#include <thread>

void r_thread_solve(R_Solution* r_solution_ptr);
void nr_thread_solve(NR_Solution* nr_solution_ptr);

int numOf_threads = 8;
std::stack<R_Solution> r_sol_stack;
std::stack<NR_Solution> nr_sol_stack;
std::mutex m;
bool target_found;




int main(int argc, char** argv)
{
		int numElements;
		PuzzlePiece** pieces;
		ifstream inputFile; //The input file stream
		ofstream outputFile; //The output file stream
		bool isValidPieces;
		PuzzlePiecesStats stats;
		bool rotatable = false;  //Whether pieces can be rotated
		string inputFilePath;
		string outputFilePath;

//&&&
		/*
		if (argc < 3 || argc > 4) //Expects minimum of 3 arguments and maximum of 4
		{
				return -1;
		}

		bool isReadInputPath = false; //Helper for parsing. Set to true after reading input path

		for (int i = 1; i < argc; i++)
		{
				string arg(argv[i]); //Convert to string for string vs. string compare
				if (argc == 4 && arg == "-rotate") //Only tries to read -rotate paramter if there are 3 argumetns
				{
						rotatable = true;
						continue;
				}
						
				//Assumes that input path will always come before output path, regardless of where -rotate is placed
				if (isReadInputPath) //If already read the input path argument
				{
						outputFilePath = arg;
				}
				else //Haven't read input path argument yet
				{
						inputFilePath = arg;
						isReadInputPath = true;
				}
						

		}




		try
		{
				outputFile.open(outputFilePath);
		}
		catch (std::system_error& e)
		{
				//Impossible to print exception in opening output file, because exception is suppsoed to be printed to the output file
				cerr << "Failed to open output file: " << outputFilePath << ". Exception: " << e.code().message();
				return -1;
		}

		try
		{
				inputFile.open(inputFilePath);
		}
		catch (std::system_error& e)
		{
				PrintMsg("Failed to open input file: " + inputFilePath + ". Exception: " + e.code().message(), &outputFile);
				return -1;
		}


		//Get jigsaw pieces from the input file
		numElements = 0;
		pieces = GetPuzzlePiecesFromInputFile(&inputFile, &outputFile, &numElements); //If returns, assumed that pieces are properly initialized

		if (pieces == NULL)
				return -1; //Encountered error during parsing and already printed it

		//Get statistics about the jigsaw pieces
		stats = GetJigsawPiecesStats(pieces, numElements);

		//Validate the stats for a genearl type of puzzle (without assuming number of rows/columns)
		isValidPieces = IsValidJigsawPiecesStats(stats, &outputFile);

//&&&
		*/

		//manual paramter setting begin
		isValidPieces = true;
		numElements = 30;
		pieces = new PuzzlePiece*[numElements];
		rotatable = false;
		int i = 0;

		/*pieces[i++] = &PuzzlePiece(1, 0, 0, 0, 0);
		pieces[i++] = &PuzzlePiece(2, 0, 0, 0, -1);
		pieces[i++] = &PuzzlePiece(3, 0, 0, -1, 0);
		pieces[i++] = &PuzzlePiece(4, 1, 1, 0, 0);*/


		

		pieces[i++] = &PuzzlePiece(1, 0, 0, 1, -1);
		pieces[i++] = &PuzzlePiece(2, -1, 0, 1, 0);
		pieces[i++] = &PuzzlePiece(3, -1, 0, -1, 1);
		pieces[i++] = &PuzzlePiece(4, 1, 0, 1, 1);
		pieces[i++] = &PuzzlePiece(5, -1, 0, 0, -1);

		pieces[i++] = &PuzzlePiece(6, 0, 1, -1, 1);
		pieces[i++] = &PuzzlePiece(7, 1, 0, 0, -1);
		pieces[i++] = &PuzzlePiece(8, 0, -1, 0, -1);
		pieces[i++] = &PuzzlePiece(9, 0, -1, -1, 0);
		pieces[i++] = &PuzzlePiece(10, 1, 1, 0, 0);

		pieces[i++] = &PuzzlePiece(11, 0, -1, 0, 0);
		pieces[i++] = &PuzzlePiece(12, 0, 1, 1, 0);
		pieces[i++] = &PuzzlePiece(13, -1, 1, 1, 0);
		pieces[i++] = &PuzzlePiece(14, -1, 0, 0, 0);
		pieces[i++] = &PuzzlePiece(15, 0, 0, 0, 0);

		// 15
		
		
		pieces[i++] = &PuzzlePiece(16, 0, 0, 1, -1);
		pieces[i++] = &PuzzlePiece(17, -1, 0, 1, 0);
		pieces[i++] = &PuzzlePiece(18, -1, 0, -1, 1);
		pieces[i++] = &PuzzlePiece(19, 1, 0, 1, 1);
		pieces[i++] = &PuzzlePiece(20, -1, 0, 0, -1);

		pieces[i++] = &PuzzlePiece(21, 0, 1, -1, 1);
		pieces[i++] = &PuzzlePiece(22, 1, 0, 0, -1);
		pieces[i++] = &PuzzlePiece(23, 0, -1, 0, -1);
		pieces[i++] = &PuzzlePiece(24, 0, -1, -1, 0);
		pieces[i++] = &PuzzlePiece(25, 1, 1, 0, 0);

		pieces[i++] = &PuzzlePiece(26, 0, -1, 0, 0);
		pieces[i++] = &PuzzlePiece(27, 0, 1, 1, 0);
		pieces[i++] = &PuzzlePiece(28, -1, 1, 1, 0);
		pieces[i++] = &PuzzlePiece(29, -1, 0, 0, 0);
		pieces[i++] = &PuzzlePiece(30, 0, 0, 0, 0);
		
		// 30
		/*
		*/

		//Attempt to solve the puzzle only if the pieces are valid
		if (isValidPieces == true)
		{

				//set general parameters: puzzle set and decomposition array
				std::vector<PuzzlePiece> puzzle_set_input;
		
				int i;
				for (i = 0; i < numElements; i++)
						puzzle_set_input.push_back(*pieces[i]);

				int numOf_decomps = how_many_decompositions(numElements, rotatable);
				int** decomp_array = new int*[numOf_decomps];
				for (i = 0; i < numOf_decomps; i++) decomp_array[i] = new int[2];
				initialize_decomp_array(decomp_array, numElements, rotatable);

				bool puzzle_solved = false;
				target_found = false;

		
				if (rotatable) {
						//Create a vector of puzzle pieces for the solution
						//A pointer-to-pointer array was used for verification, whereas a vector will be used for the solution
						
		
						for (unsigned i = 0; i < puzzle_set_input.size(); i++)
						{
								puzzle_set_input[i].set_piece_type_and_symetry_factor();
						}
		
						
						R_Repository r_repository(puzzle_set_input, numElements);
		
						// TRY TO SOLVE BY EACH DECOMPOSITION
						for (int i = 0; i < numOf_decomps; i++)
						{
								int height = decomp_array[i][0];
								int width = decomp_array[i][1];

								R_Solution r_solution(r_repository, height, width, rotatable);
								R_Solution r_final_solution(r_repository, height, width, rotatable);

								r_sol_stack.push(r_solution);

								std::thread* thread_arr = new std::thread[numOf_threads];
								for (int i = 0; i < numOf_threads; i++) thread_arr[i] = std::thread(r_thread_solve, &r_final_solution);

								for (int i = 0; i < numOf_threads; i++) thread_arr[i].join();
								delete[] thread_arr;

								if (r_final_solution.is_solved())
								{
									puzzle_solved = true;
									std::cout << "puzzle solved!\n\n" << std::endl;
//&&&								r_final_solution.print_to_file(&outputFile);
									break;
								}
						}

						if (puzzle_solved == false)
						{
								std::cout << "puzzle unsolvable\n\n" << std::endl;
//&&&							PrintMsg("Cannot solve puzzle: it seems that there is no proper solution", &outputFile);
						}

				}

				else    // unrotatable case
				{

					NR_Repository nr_repository(puzzle_set_input, numElements);

					// TRY TO SOLVE BY EACH DECOMPOSITION
					for (int i = 0; i < numOf_decomps; i++)
					{
						int height = decomp_array[i][0];
						int width = decomp_array[i][1];

						NR_Solution nr_solution(nr_repository, height, width);
						NR_Solution nr_final_solution(nr_repository, height, width);

						nr_sol_stack.push(nr_solution);

						std::thread* thread_arr = new std::thread[numOf_threads];
						for (int i = 0; i < numOf_threads; i++) thread_arr[i] = std::thread(nr_thread_solve, &nr_final_solution);

						for (int i = 0; i < numOf_threads; i++) thread_arr[i].join();
						delete[] thread_arr;

						if (nr_final_solution.is_solved())
						{
							puzzle_solved = true;
							std::cout << "puzzle solved!\n\n" << std::endl;
//&&&						r_final_solution.print_to_file(&outputFile);
							break;
						}
					}


					if (puzzle_solved == false)
					{
						std::cout << "puzzle unsolvable\n\n" << std::endl;
						//&&&							PrintMsg("Cannot solve puzzle: it seems that there is no proper solution", &outputFile);
					}
				}
			// FREE DECOMPOSITION MEMORY
			for (i = 0; i < numOf_decomps; i++) delete[] decomp_array[i];
			delete[] decomp_array;
		}

		// FREE PUZZLE MEMORY
		delete[] pieces;
		system("pause");
		return 0;
}




void r_thread_solve(R_Solution* r_solution_ptr) {
	bool unlocked_already;
	while (true) {

		unlocked_already = false;
		m.lock();

		if (target_found || r_sol_stack.empty()) { m.unlock(); break; }

		R_Solution temp_sol = r_sol_stack.top();

		r_sol_stack.pop();

		if (temp_sol.is_solved()) {
			target_found = true;
			*r_solution_ptr = temp_sol;
			std::cout << "puzzle solved!\n\n\n\n";
			m.unlock();
			break;
		}

		// If it is not solved, further search must be conducted, but the operations before creating
		// new solution states and pushing them into the stack, are quite heavy. If the number of solutions
		// in stack is greater than the number of possibly waiting threads, than those operations can be
		// executed after the lock is released (or otherwise the invariant, that while the stack is not 
		// empty - a solution may still be found, will be inconsistent). Therefore, the pre-operations called
		// by algorithm_1st_half_step are performed either before or after the lock release, abiding the
		// above condition check.
		
		if (!r_sol_stack.empty()) { 

		//if (sol_stack.size() > numOf_threads) {
			unlocked_already = true;
			m.unlock();
		}

		std::stack<R_Solution> temp_stack;
		temp_sol.algorithm_step(&temp_stack);
		
		if (unlocked_already) { unlocked_already = false; m.lock(); }

		while (!temp_stack.empty()) {
			r_sol_stack.push(temp_stack.top());
			temp_stack.pop();
		}

		m.unlock();
	}
}


void nr_thread_solve(NR_Solution* nr_solution_ptr) {
	bool unlocked_already;
	while (true) {

		unlocked_already = false;
		m.lock();

		if (target_found || nr_sol_stack.empty()) { m.unlock(); break; }

		NR_Solution temp_sol = nr_sol_stack.top();

		nr_sol_stack.pop();

		if (temp_sol.is_solved()) {
			target_found = true;
			*nr_solution_ptr = temp_sol;
			std::cout << "puzzle solved!\n\n\n\n";
			m.unlock();
			break;
		}

		if (!nr_sol_stack.empty()) {

			unlocked_already = true;
			m.unlock();
		}

		std::stack<NR_Solution> temp_stack;
		temp_sol.algorithm_step(&temp_stack);

		if (unlocked_already) { unlocked_already = false; m.lock(); }

		while (!temp_stack.empty()) {
			nr_sol_stack.push(temp_stack.top());
			temp_stack.pop();
		}

		m.unlock();
	}
}