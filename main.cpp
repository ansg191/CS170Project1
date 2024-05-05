#include <iostream>

#include "Problem.h"
#include "Puzzle.h"

#include "frontiers/BreadthFirstSearch.h"

int main()
{
	uint8_t init[3][3] = {
	        {0, 2, 3},
		{1, 4, 5},
		{6, 7, 8}
	};
	Puzzle<3> initBoard(init);

	uint8_t goal[3][3] = {
	        {1, 2, 3},
	        {4, 7, 5},
	        {6, 0, 8}};
	Puzzle<3> goalBoard(goal);

	Problem problem = Problem(initBoard, goalBoard);

	BreadthFirstSearch<Puzzle<3>> bfs;

	auto result = problem.solve(&bfs);

	if (result) {
		std::cout << "Solution found!" << std::endl;
		while (result->parent) {
			std::cout << result->data << std::endl;
			result = result->parent;
		}
		std::cout << result->data << std::endl;
	} else
		std::cout << "No solution found." << std::endl;

	return 0;
}
