#include "Problem.h"
#include "Puzzle.h"
#include <iostream>

int main()
{
	uint8_t board[3][3] = {
		{0, 2, 3},
		{1, 4, 5},
		{6, 7, 8}
	};
	Puzzle<3> puzzle(board);

	Problem problem = Problem(puzzle, puzzle);

	return 0;
}
