//
// Created by Anshul Gupta on 5/5/24.
//

#ifndef CS170PROJECT1_BREADTHFIRSTSEARCH_H
#define CS170PROJECT1_BREADTHFIRSTSEARCH_H

#include <deque>

#include "../Frontier.h"

template<class T>
class BreadthFirstSearch : public Frontier<T> {
public:
	void pushNode(Node<T> *node) override;
	Node<T> *popNode() override;
	bool contains(T data) const override;

private:
	std::deque<Node<T> *> queue;
};

template<class T>
void BreadthFirstSearch<T>::pushNode(Node<T> *node)
{
	queue.push_back(node);
	if (queue.size() > this->maxQueueSize)
		this->maxQueueSize = queue.size();
}

template<class T>
Node<T> *BreadthFirstSearch<T>::popNode()
{
	if (queue.empty())
		return nullptr;

	Node<T> *node = queue.front();
	queue.pop_front();
	return node;
}

template<class T>
bool BreadthFirstSearch<T>::contains(T data) const
{
	for (Node<T> *node: queue)
		if (node->data == data)
			return true;

	return false;
}


#endif//CS170PROJECT1_BREADTHFIRSTSEARCH_H
