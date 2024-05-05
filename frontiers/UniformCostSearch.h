//
// Created by Anshul Gupta on 5/5/24.
//

#ifndef CS170PROJECT1_UNIFORMCOSTSEARCH_H
#define CS170PROJECT1_UNIFORMCOSTSEARCH_H

#include <algorithm>

#include "../Frontier.h"

template<class T>
class UniformCostSearch : public Frontier<T> {
public:
	void pushNode(Node<T> *node) override;
	Node<T> *popNode() override;
	bool contains(T data) const override;

private:
	struct NodeInternal {
		Node<T> *node;
		size_t depth;

		explicit NodeInternal(Node<T> *n) : node(n), depth(n->getDepth()) {}

		bool operator<(const NodeInternal &rhs) const { return depth < rhs.depth; }
		bool operator>(const NodeInternal &rhs) const { return rhs < *this; }
	};

	/// Priority queue (min heap) of nodes
	std::vector<NodeInternal> queue;
};

template<class T>
void UniformCostSearch<T>::pushNode(Node<T> *node)
{
	queue.emplace_back(node);
	std::push_heap(queue.begin(), queue.end(), std::greater<>());

	if (queue.size() > this->maxQueueSize)
		this->maxQueueSize = queue.size();
}

template<class T>
Node<T> *UniformCostSearch<T>::popNode()
{
	if (queue.empty())
		return nullptr;

	NodeInternal node = queue.front();
	std::pop_heap(queue.begin(), queue.end(), std::greater<>());
	queue.pop_back();

	std::cout << "The best state to expand with a g(n) = " << node.depth
	          << " is..." << std::endl;
	std::cout << node.node->data << std::endl;

	return node.node;
}

template<class T>
bool UniformCostSearch<T>::contains(T data) const
{
	for (const NodeInternal &node: queue) {
		if (node.node->data == data)
			return true;
	}
	return false;
}

#endif//CS170PROJECT1_UNIFORMCOSTSEARCH_H
