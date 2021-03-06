#include "main.h"

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


		//Attempt to solve the puzzle only if the pieces are valid
		if (isValidPieces == true)
		{

				//Create a vector of puzzle pieces for the solution
				//A pointer-to-pointer array was used for verification, whereas a vector will be used for the solution
				std::vector<PuzzlePiece> puzzle_set_input;

				for (int i = 0; i < numElements; i++)
						puzzle_set_input.push_back(*pieces[i]);


				for (int i = 0; i < puzzle_set_input.size(); i++)
				{
						puzzle_set_input[i].set_piece_type_and_symetry_factor();
				}

				
				Repository repository(puzzle_set_input, numElements);

				// initialize decompositions
				int numOf_decomps = how_many_decompositions(numElements, rotatable);
				int** decomp_array = new int*[numOf_decomps];

				for (int i = 0; i < numOf_decomps; i++)
				{
						decomp_array[i] = new int[2];
				}
				initialize_decomp_array(decomp_array, numElements);



				// TRY TO SOLVE BY EACH DECOMPOSITION
				for (int i = 0; i < numOf_decomps; i++)
				{
						int height = decomp_array[i][0];
						int width = decomp_array[i][1];
						Solution solution(repository, height, width, true);
						Solution::set_solved(false);

						solution.algorithm_step();
						if (Solution::is_solved())
						{
								std::cout << "puzzle solved!\n\n" << std::endl;
								solution.print_to_file(&outputFile);
								break;
						}
				}

				if (Solution::is_solved() == false)
				{
						std::cout << "puzzle unsolvable\n\n" << std::endl;
						PrintMsg("Cannot solve puzzle: it seems that there is no proper solution", &outputFile);
				}

				
		}

		// FREE PUZZLE MEMORY
		delete[] pieces;

		return 0;
}