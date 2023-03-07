#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <functional>

template <typename T>
class BinaryTreeNode
{
public:
	T value;
	std::unique_ptr<BinaryTreeNode> left;
	std::unique_ptr<BinaryTreeNode> right;

	BinaryTreeNode(
		T value,
		std::unique_ptr<BinaryTreeNode> left = nullptr,
		std::unique_ptr<BinaryTreeNode> right = nullptr
	) : value(std::move(value)),
		left(std::move(left)),
		right(std::move(right))
	{}

	void bypass_straight(const std::function<void(const T&)>& acceptor)
	{
		acceptor(value);
		if (left)
			left->bypass_straight(acceptor);
		if (right)
			right->bypass_straight(acceptor);
	}
};

#endif
