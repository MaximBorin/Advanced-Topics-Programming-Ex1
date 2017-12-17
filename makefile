COMP = g++-5.3.0
#put all your object files here
OBJS = main.o Auxiliary.o NR_Position.o NR_Repository.o NR_Slot.o NR_Solution.o Position.o PuzzlePiece.o PuzzlePiecesStats.o R_Position.o R_Repository.o R_Slot.o R_Solution.o Repository.o Slot.o Solution.o Utils.o
#The executabel filename DON'T CHANGE
EXEC = ex2
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
#a rule for building a simple c++ source file
#use g++-5.3.0 -MM main.cpp to see dependencies
main.o: main.cpp main.h PuzzlePiecesStats.h PuzzlePiece.h Utils.h \
 R_Position.h R_Repository.h R_Slot.h R_Solution.h Auxiliary.h \
 NR_Position.h NR_Repository.h NR_Slot.h NR_Solution.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Auxiliary.o: Auxiliary.cpp Auxiliary.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
NR_Position.o: NR_Position.cpp NR_Position.h NR_Repository.h \
 PuzzlePiece.h Utils.h NR_Slot.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
NR_Repository.o: NR_Repository.cpp NR_Repository.h PuzzlePiece.h Utils.h \
 NR_Slot.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
NR_Slot.o: NR_Slot.cpp NR_Slot.h PuzzlePiece.h Utils.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
NR_Solution.o: NR_Solution.cpp NR_Solution.h NR_Position.h \
 NR_Repository.h PuzzlePiece.h Utils.h NR_Slot.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Position.o: Position.cpp Position.h Repository.h PuzzlePiece.h Utils.h \
 Slot.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
PuzzlePiece.o: PuzzlePiece.cpp PuzzlePiece.h Utils.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
PuzzlePiecesStats.o: PuzzlePiecesStats.cpp PuzzlePiecesStats.h \
 PuzzlePiece.h Utils.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
R_Position.o: R_Position.cpp R_Position.h R_Repository.h PuzzlePiece.h \
 Utils.h R_Slot.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
R_Repository.o: R_Repository.cpp R_Repository.h PuzzlePiece.h Utils.h \
 R_Slot.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
R_Slot.o: R_Slot.cpp R_Slot.h PuzzlePiece.h Utils.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
R_Solution.o: R_Solution.cpp R_Solution.h R_Position.h R_Repository.h \
 PuzzlePiece.h Utils.h R_Slot.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Repository.o: Repository.cpp Repository.h PuzzlePiece.h Utils.h Slot.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Slot.o: Slot.cpp Slot.h PuzzlePiece.h Utils.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Solution.o: Solution.cpp Solution.h Position.h Repository.h PuzzlePiece.h \
 Utils.h Slot.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Utils.o: Utils.cpp Utils.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
 
clean:
	rm -f $(OBJS) $(EXEC)