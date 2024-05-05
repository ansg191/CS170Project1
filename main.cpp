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

	std::cout << "Hello, World!" << std::endl;

	std::cout << puzzle << std::endl;

	auto availableMoves = puzzle.availableMoves();
	for (const auto &move : availableMoves) {
		std::cout << move << std::endl;
	}

	return 0;
}
