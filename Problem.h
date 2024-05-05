//
// Created by Anshul Gupta on 5/4/24.
//

#ifndef CS170PROJECT1_PROBLEM_H
#define CS170PROJECT1_PROBLEM_H

#include <optional>
#include <set>

#include "Frontier.h"
#include "Puzzle.h"
#include "Tree.h"

class Problem {
public:
	constexpr static size_t SIZE = 3;
	typedef Puzzle<SIZE> State;

	Problem(State init, State goal) : tree(init), goal(goal) {}

	std::optional<State> solve(Frontier<State> *frontier);

private:
	Tree<State> tree;
	State goal;
};

#endif//CS170PROJECT1_PROBLEM_H
