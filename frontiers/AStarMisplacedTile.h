//
// Created by Anshul Gupta on 5/5/24.
//

#ifndef CS170PROJECT1_ASTARMISPLACEDTILE_H
#define CS170PROJECT1_ASTARMISPLACEDTILE_H

#include <optional>

#include "../Frontier.h"
#include "../Puzzle.h"

/**
 * @class AStarMisplacedTile
 * @brief A class that implements the A* search algorithm using the number of misplaced tiles as the heuristic.
 *
 * The A* algorithm uses a priority queue (min-heap) to prioritize nodes based on the sum of the depth of the
 * node and the number of misplaced tiles.
 *
 * f(n) = g(n) + h(n)
 * where g(n) is the depth of the node and h(n) is the number of misplaced tiles.
 *
 * @tparam N The size of the puzzle board.
 *
 * @see Frontier
 */
template<size_t N>
class AStarMisplacedTile : public Frontier<Puzzle<N>> {
public:
	AStarMisplacedTile() : goal(std::nullopt) {}

	void initialize(Puzzle<N> g) override { this->goal = g; }
	void pushNode(Node<Puzzle<N>> *node) override;
	Node<Puzzle<N>> *popNode() override;
	bool contains(Puzzle<N> data) const override;

private:
	/// Internal representation of a node in the min heap
	struct NodeInternal {
		/// Pointer to the node state
		Node<Puzzle<N>> *node;
		/// Depth of the node
		size_t depth;
		/// Number of misplaced tiles
		size_t misplacedTiles;

		explicit NodeInternal(Node<Puzzle<N>> *n, size_t misplaced)
		    : node(n), depth(n->getDepth()), misplacedTiles(misplaced) {}

		bool operator<(const NodeInternal &rhs) const
		{
			// f(n) = g(n) + h(n)
			// g(n) = depth
			// h(n) = misplacedTiles
			return (depth + misplacedTiles) < (rhs.depth + rhs.misplacedTiles);
		}
		bool operator>(const NodeInternal &rhs) const { return rhs < *this; }
	};

	/// The goal state
	std::optional<Puzzle<N>> goal;
	/// Priority queue (min heap) of nodes
	std::vector<NodeInternal> queue;
};

template<size_t N>
void AStarMisplacedTile<N>::pushNode(Node<Puzzle<N>> *node)
{
	// Calculate the number of misplaced tiles
	if (!this->goal.has_value())
		throw std::runtime_error("Goal state not set");
	size_t misplaced = node->data.countMisplacedTiles(this->goal.value());

	// Insert the node into the min heap
	this->queue.emplace_back(node, misplaced);
	std::push_heap(this->queue.begin(), this->queue.end(), std::greater<>());

	// Update the max queue size statistic
	if (this->queue.size() > this->maxQueueSize)
		this->maxQueueSize = this->queue.size();
}

template<size_t N>
Node<Puzzle<N>> *AStarMisplacedTile<N>::popNode()
{
	if (this->queue.empty())
		return nullptr;

	// Remove the node with the lowest cost
	NodeInternal node = this->queue.front();
	std::pop_heap(this->queue.begin(), this->queue.end(), std::greater<>());
	this->queue.pop_back();

	std::cout << "The best state to expand with a g(n) = " << node.depth << " and h(n) = " << node.misplacedTiles
	          << " is..." << std::endl;
	std::cout << node.node->data << std::endl;

	return node.node;
}

template<size_t N>
bool AStarMisplacedTile<N>::contains(Puzzle<N> data) const
{
	for (const auto &node: this->queue) {
		if (node.node->data == data)
			return true;
	}
	return false;
}

#endif//CS170PROJECT1_ASTARMISPLACEDTILE_H
