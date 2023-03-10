#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <memory>

using std::make_unique;
using std::unique_ptr;

template <typename T>
class LinkedList
{
public:
	struct Node;
	using NodePtr = Node*;

	struct Node
	{
		T value;
		NodePtr next = nullptr;

		Node(T value)
		{
			this->value = std::move(value);
			next = nullptr;
		}
		Node(T value, NodePtr next)
		{
			this->value = std::move(value);
			this->next = next;
		}
	};

	LinkedList(LinkedList&& another) noexcept = default;
	LinkedList& operator=(LinkedList&& another) noexcept = default;

	LinkedList(std::initializer_list<T> list)
		: first_node_(0),
		last_node_(&first_node_),
		size_(list.size())
	{
		const T* begin = list.begin();

		last_node_->value = std::move(*begin);

		++begin;

		for (; begin != list.end(); ++begin)
		{
			add(*begin);
		}
	}

	~LinkedList()
	{
		NodePtr current = first_node_.next;
		while (current != nullptr)
		{
			NodePtr next = current->next;
			delete current;
			current = next;
		}
	}

	void add(T value)
	{
		last_node_->next = new Node(std::move(value));
		last_node_ = last_node_->next;
		++size_;
	}

	void insert(size_t index, T value)
	{
		NodePtr current = get(index);
		*current = Node(
				value, 
				new Node(std::move(*current))
		);
		size_++;
		if (current == last_node_)
			last_node_ = last_node_->next;
	}

	void pop(size_t index)
	{
		size_--;
		if (index == 0) {
			first_node_ = std::move(*first_node_.next);
			return;
		}

		NodePtr previous = get(index - 1);

		if (index == size_)
		{
			delete previous->next;
			last_node_ = previous;
			return;
		}

		const NodePtr to_delete = previous->next;
		previous->next = previous->next->next;
		delete to_delete;
	}

	T& operator[](size_t index) {
		return get(index)->value;
	}

	const T& operator[](size_t index) const {
		return get(index)->value;
	}

	[[nodiscard]] const size_t& size() const
	{
		return size_;
	}

    template <typename U>
    friend std::ostream& operator<<(
            std::ostream& in,
            LinkedList<U>& list
    );
private:
    Node first_node_;
	NodePtr last_node_{&first_node_};
	size_t size_;

	NodePtr get(size_t index) {
		NodePtr selected{ &first_node_ };

		for (size_t i = 0; i < index; i++)
		{
			if (selected == nullptr)
				throw std::out_of_range(
					"index is out of boundaries"
				);
			selected = selected->next;
		}

		return selected;
	}
};

template <typename T>
std::ostream& operator<<(
	std::ostream& in,
	LinkedList<T>& list
	)
{
	using NodePtr = typename LinkedList<T>::Node const*;

    NodePtr current = &list.first_node_;

	while (current->next != nullptr)
	{
		in << current->value << " -> ";
		current = current->next;
	}
	in << current->value << '\n';

	return in;
}

//template <typename T>
//bool is_looped_list(const Node<T>& list)
//{
//	Node<T> const* faster = &list;
//	Node<T> const* slower = &list;
//	do {
//		if (faster->next == nullptr
//			|| faster->next->next == nullptr)
//			return false;
//		faster = faster->next->next;
//		slower = slower->next;
//	} while (faster != slower);
//
//	return true;
//}

#endif