Late submission of 5 days was approved by Natan. We attached his email message in these formats: NatanEmail.jpg (screenshot) and NatanEmail.EML. The reason for deadline extension is in Miluim.pdf.



solution strategy description:


1. once a valid data set is extracted from file - each valid puzzle set rectangular decomposition of the puzzle-set size is checked


2. if none of the compositions fits a plausible decomposition - the puzzle is not checked, and a fitting error message is put to file


3. any of the remaining "good" decompositions is being checked in the following manner

3.1 in each recursive iteration - the "best next position" is being looked for.

3.2 by "best next position" we mean - the position for which there is the least number of possible fitting pieces from the remaining non-assigned puzzle pieces.

3.2.1 for instance - the best position possible is one with zero fitting pieces, which will lead to the imediate termination of the recursion branch

3.3 each piece being fit to the puzzle, leads to either one of two continuations:

3.3.1 if there are no remaining non-assigned puzzle pieces - then the solution in the branch is copied to the final solution, and all recursion branches return to the caller - hence, the search terminated.

3.3.2 if there are remaining non_assigned puzzle pieces - then a "best next position" is being looked for, and the recursion call branches for every piece fitting that position.


4. optimization features

4.1 as this is an exponential solution, the optimizations only serve to minimize the exponential factor.

4.1.1 no duplicates are allowed to be checked - i.e. for each position the recursive call will avoid checking two identical piece continuations.

4.1.2 best next position ensures "greedily" that the recursion will branch to the minimal possible number.

4.1.2.1 formally: next position = argmin(position) {position.numOf_position_fitting_pieces} (variable names only for illustration).

4.1.2.2 by "greedily" we mean that the best next position is checked to the extent of depth = 1, with no contingencies

4.2 time complexity cost in current implementation:

4.2.1 "no duplicates": O(n^2)

4.2.2 "best next position": O(n^3)


5. further optimizations planned but not implemented

5.1 strategy choice by data characterization - for nearly unduplicated data set, there might be no need to check for duplizates every time.

5.2 maintaing a datastructure that will save for each slot the number of fitting unique pieces.

5.2.1 this can decrease 4.2.2 time complexity at least to O(n^2).

5.2.2 on the other hand - this will increase space complexity immensely.
