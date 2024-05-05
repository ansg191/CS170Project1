//
// Created by Anshul Gupta on 5/4/24.
//

#ifndef CS170PROJECT1_TREE_H
#define CS170PROJECT1_TREE_H

#include <cstdlib>
#include <stdexcept>

/**
 * @class Node
 * @brief A template class representing a node in a tree structure.
 *
 * This class is designed to be used as nodes in a tree data structure. Each node contains
 * a piece of data, a pointer to its parent node (if it exists), and up to 4 pointers to its
 * child nodes.
 *
 * @tparam T The type of data to be stored in the node.
 */
template<class T>
struct Node {
	/// Data stored in the node
	T data;

	/// Pointer to the parent node, if it exists
	Node<T> *parent;

	/// Pointer to at most 4 children nodes
	Node<T> *children[4];
	/// Number of children nodes
	size_t numChildren;

	explicit Node(T data, Node<T> *parent = nullptr)
	    : data(data), parent(parent), numChildren(0)
	{
		for (size_t i = 0; i < 4; i++)
			this->children[i] = nullptr;
	}

	Node(const Node &other) = delete;
	Node(Node &&other) = delete;

	~Node()
	{
		for (size_t i = 0; i < this->numChildren; i++)
			delete this->children[i];
	}

	/**
	 * @brief Add a child node to the current node.
	 * @param d The data to be stored in the child node.
	 */
	Node<T> *addChild(T d)
	{
		if (this->numChildren >= 4)
			throw std::runtime_error("Cannot add more than 4 children to a node");

		auto *child = new Node<T>(d, this);
		this->children[this->numChildren++] = child;
		return child;
	}

	/**
	 * @brief Get the path from the current node to the root node.
	 *
	 * @tparam T The type of data stored in the node.
	 * @return std::vector<T> The path from the current node to the root node.
	 */
	std::vector<T> getPath() const
	{
		std::vector<T> path;
		const Node<T> *current = this;
		while (current) {
			path.push_back(current->data);
			current = current->parent;
		}
		std::reverse(path.begin(), path.end());
		return path;
	}

	/// Get the depth of the node in the tree
	[[nodiscard]]
	size_t getDepth() const
	{
		size_t depth = 0;
		const Node<T> *current = this;
		while (current) {
			depth++;
			current = current->parent;
		}
		return depth - 1;
	}
};

/**
 * @brief A tree data structure
 *
 * Stores data in a tree structure. Each node can have at most 4 children.
 * The nodes are owned by the tree and are deleted when the tree is deleted.
 *
 * @tparam T The type of data stored in the tree
 */
template<class T>
class Tree {
public:
	explicit Tree(T data) { this->root = new Node<T>(data); }
	Tree(const Tree &other) = delete;
	Tree(Tree &&other) = delete;
	~Tree() { delete this->root; }

	Node<T> *getRoot() { return this->root; }

private:
	/// The root node of the tree
	Node<T> *root;
};

#endif//CS170PROJECT1_TREE_H
