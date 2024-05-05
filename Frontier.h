//
// Created by Anshul Gupta on 5/5/24.
//

#ifndef CS170PROJECT1_FRONTIER_H
#define CS170PROJECT1_FRONTIER_H

#include "Tree.h"

/**
 * @class Frontier
 * @brief A generic interface for frontier data structures used in traversal algorithms.
 *
 * @tparam T The type of the state stored in the nodes.
 */
template<class T>
class Frontier {
public:
	virtual ~Frontier() = default;

	/// Initialize the frontier with the goal state if necessary
	virtual void initialize(T goal) {}

	/// Add a node to the frontier. Should silently ignore if the node is already in the frontier
	virtual void pushNode(Node<T> *node) = 0;
	/// Remove and return the top node from the frontier
	virtual Node<T> *popNode() = 0;

	/// Check if the frontier contains a node with the given data
	virtual bool contains(T data) const = 0;

	/// Get the maximum number of nodes in the frontier queue at any given time
	[[nodiscard]] size_t getMaxQueueSize() const { return maxQueueSize; }

protected:
	size_t maxQueueSize = 0;
};

#endif//CS170PROJECT1_FRONTIER_H
