#include <iostream>

#include "Problem.h"
#include "Puzzle.h"

#include "frontiers/AStarMisplacedTile.h"
#include "frontiers/BreadthFirstSearch.h"
#include "frontiers/UniformCostSearch.h"

Puzzle<3> requestInitState()
{
	constexpr uint8_t DEFAULT_INIT[3][3] = {
	        {0, 2, 3},
	        {1, 4, 5},
	        {6, 7, 8}};

	std::cout << "Type “1” to use a default puzzle, or “2” to enter your own puzzle." << std::endl;

	int input;
	std::cin >> input;

	if (input == 1)
		return Puzzle<3>(DEFAULT_INIT);

	int init[3][3];
	std::cout << "Enter your puzzle, use a zero to represent the blank" << std::endl;

	std::cout << "Enter the first row, use space or tabs between numbers" << std::endl;
	std::cin >> init[0][0] >> init[0][1] >> init[0][2];

	std::cout << "Enter the second row, use space or tabs between numbers" << std::endl;
	std::cin >> init[1][0] >> init[1][1] >> init[1][2];

	std::cout << "Enter the third row, use space or tabs between numbers" << std::endl;
	std::cin >> init[2][0] >> init[2][1] >> init[2][2];

	uint8_t initPuzzle[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			initPuzzle[i][j] = init[i][j];

	return Puzzle<3>(initPuzzle);
}

std::unique_ptr<Frontier<Puzzle<3>>> requestAlgo()
{
	std::cout << "Enter your choice of algorithm" << std::endl;
	std::cout << "0. Breadth First Search" << std::endl;
	std::cout << "1. Uniform Cost Search" << std::endl;
	std::cout << "2. A* with the Misplaced Tile heuristic" << std::endl;
	std::cout << "3. A* with the Manhattan distance heuristic" << std::endl;

	uint input;
	std::cin >> input;

	switch (input) {
	case 0:
		return std::make_unique<BreadthFirstSearch<Puzzle<3>>>();
	case 1:
		return std::make_unique<UniformCostSearch<Puzzle<3>>>();
	case 2:
		return std::make_unique<AStarMisplacedTile<3>>();
	default:
		std::cout << "Invalid input. Please try again." << std::endl;
		return requestAlgo();
	}
}

void printStats(Problem &problem, Frontier<Puzzle<3>> *algo, Node<Puzzle<3>> *result)
{
	std::cout << "The total number of nodes expanded: " << problem.getNumExpanded() << std::endl;
	std::cout << "The maximum number of nodes in the queue at any one time: " << algo->getMaxQueueSize() << std::endl;

	if (result)
		std::cout << "The depth of the goal node: " << result->getDepth() << std::endl;
}

int main()
{
	std::cout << "Welcome to Anshul Gupta's (agupt109) 8 puzzle solver" << std::endl;

	Puzzle<3> init = requestInitState();

	uint8_t goal[3][3] = {
	        {1, 2, 3},
	        {4, 5, 6},
	        {7, 8, 0}};
	Puzzle<3> goalBoard(goal);

	Problem problem = Problem(init, goalBoard);

	auto algo = requestAlgo();

	auto result = problem.solve(algo.get());

	if (result) {
		std::cout << "Solution found!" << std::endl;

		auto path = result->getPath();
		for (const auto &p: path) {
			std::cout << p << std::endl;
		}
	} else {
		std::cout << "No solution found." << std::endl;
	}

	printStats(problem, algo.get(), result);

	return 0;
}
