//
// Created by Anshul Gupta on 5/5/24.
//

#ifndef CS170PROJECT1_ASTAREUCLIDEAN_H
#define CS170PROJECT1_ASTAREUCLIDEAN_H

#include <optional>

#include "../Frontier.h"
#include "../Puzzle.h"

template<size_t N>
class AStarEuclidean : public Frontier<Puzzle<N>> {
public:
	AStarEuclidean() : goal(std::nullopt) {}

	void initialize(Puzzle<N> g) override { this->goal = g; }
	void pushNode(Node<Puzzle<N>> *node) override;
	Node<Puzzle<N>> *popNode() override;
	bool contains(Puzzle<N> data) const override;

private:
	struct NodeInternal {
		Node<Puzzle<N>> *node;
		size_t depth;
		double distance;

		explicit NodeInternal(Node<Puzzle<N>> *n, double dist)
		    : node(n), depth(n->getDepth()), distance(dist) {}

		bool operator<(const NodeInternal &rhs) const
		{
			// f(n) = g(n) + h(n)
			// g(n) = depth
			// h(n) = euclidean distance
			return (distance + depth) < (rhs.distance + rhs.depth);
		}
		bool operator>(const NodeInternal &rhs) const { return rhs < *this; }
	};

	/// The goal state
	std::optional<Puzzle<N>> goal;
	/// Priority queue (min heap) of nodes
	std::vector<NodeInternal> queue;
};

template<size_t N>
void AStarEuclidean<N>::pushNode(Node<Puzzle<N>> *node)
{
	// Calculate the euclidean distance
	if (!this->goal.has_value())
		throw std::runtime_error("Goal state not set");
	double dist = node->data.calcEuclidDist(this->goal.value());

	// Insert the node into the min heap
	this->queue.emplace_back(node, dist);
	std::push_heap(this->queue.begin(), this->queue.end(), std::greater<>());

	// Update the max queue size statistic
	if (this->queue.size() > this->maxQueueSize)
		this->maxQueueSize = this->queue.size();
}

template<size_t N>
Node<Puzzle<N>> *AStarEuclidean<N>::popNode()
{
	if (this->queue.empty())
		return nullptr;

	NodeInternal node = this->queue.front();
	std::pop_heap(this->queue.begin(), this->queue.end(), std::greater<>());
	this->queue.pop_back();

	std::cout << "The best state to expand with a g(n) = " << node.depth << " and h(n) = " << node.distance
	          << " is..." << std::endl;
	std::cout << node.node->data << std::endl;

	return node.node;
}

template<size_t N>
bool AStarEuclidean<N>::contains(Puzzle<N> data) const
{
	for (const auto &node: this->queue) {
		if (node.node->data == data)
			return true;
	}
	return false;
}

#endif//CS170PROJECT1_ASTAREUCLIDEAN_H
