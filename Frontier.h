//
// Created by Anshul Gupta on 5/5/24.
//

#ifndef CS170PROJECT1_FRONTIER_H
#define CS170PROJECT1_FRONTIER_H

#include "Tree.h"

template<class T>
class Frontier {
public:
	virtual ~Frontier() = default;

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
