#ifndef STACK_H
#define STACK_H

#include "DynamicArray.hpp"

template <typename T>
class Stack :
	DynamicArray<T>,
	IPushable<T>,
	IPopable<T>
{
public:
	using DArray = DynamicArray<T>;

	Stack(std::initializer_list<T> list)
		: DArray(list)
	{}

	Stack(DArray array)
		: DArray(std::move(array))
	{}

	void push(T element) override
	{
		DArray::append(std::move(element));
	}

	T pop() override
	{
		const size_t last_index = DArray::size() - 1;
		T element = std::move((*this)[last_index]);

		DArray::pop(last_index);

		return element;
	}

	bool is_empty() const
	{
		return DArray::is_empty();
	}

	const T& last() const
	{
		return (*this)[DArray::size() - 1];
	}
};

#endif