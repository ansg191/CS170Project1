//
// Created by Anshul Gupta on 5/4/24.
//

#ifndef CS170PROJECT1_PROBLEM_H
#define CS170PROJECT1_PROBLEM_H

#include "Frontier.h"
#include "Puzzle.h"
#include "Tree.h"

class Problem {
public:
	constexpr static size_t SIZE = 3;
	typedef Puzzle<SIZE> State;

	Problem(State init, State goal) : tree(init), goal(goal) {}

	/**
	 * Solve the problem using the given frontier
	 * @param frontier Frontier to use for solving the problem
	 * @return Node containing the solution, or nullptr if no solution was found
	 */
	Node<State> *solve(Frontier<State> *frontier);

	[[nodiscard]] size_t getNumExpanded() const { return numExpanded; }

private:
	Tree<State> tree;
	State goal;

	/// Number of nodes expanded during the search
	size_t numExpanded = 0;
};

#endif//CS170PROJECT1_PROBLEM_H
