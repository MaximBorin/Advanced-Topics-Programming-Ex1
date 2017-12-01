COMP = g++-5.3.0
#put all your object files here
OBJS = main.o auxiliary.o PuzzlePiecesStats.o PuzzlePiece.o Solution.o Utils.o 
#The executabel filename DON'T CHANGE
EXEC = ex1
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp main.h PuzzlePiecesStats.h PuzzlePiece.h Utils.h auxiliary.h Solution.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
auxiliary.o: auxiliary.cpp auxiliary.h PuzzlePiece.h Utils.h Solution.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
PuzzlePiecesStats.o: PuzzlePiecesStats.cpp PuzzlePiecesStats.h PuzzlePiece.h Utils.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
PuzzlePiece.o: PuzzlePiece.cpp PuzzlePiece.h Utils.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Solution.o: Solution.cpp Solution.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Utils.o: Utils.cpp Utils.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)