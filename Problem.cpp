//
// Created by Anshul Gupta on 5/4/24.
//

#include "Problem.h"

std::optional<Problem::State> Problem::solve(Frontier<State> *frontier)
{
	std::set<State, std::equal_to<>> explored;
	frontier->pushNode(this->tree.getRoot());

	Node<State> *node;
	while ((node = frontier->popNode()) != nullptr) {
		// If the node contains the goal state, return the solution
		if (node->data == this->goal)
			return node->data;

		// Add the node to the explored set
		explored.insert(node->data);

		// Expand the node and add its children to the frontier
		auto children = node->data.availableMoves();
		for (auto child: children) {
			// Check if the child is already explored or in the frontier
			if (explored.contains(child)) continue;
			if (frontier->contains(child)) continue;

			Node<State> *childNode = node->addChild(child);
			frontier->pushNode(childNode);
		}
	}

	// No solution found, failure
	return {};
}
