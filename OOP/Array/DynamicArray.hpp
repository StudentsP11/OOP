#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.hpp"
#include "ISequence.hpp"

template <typename T>
class DynamicArray
	: public Array<T>,
	public IIndexedPopable<T>
{
public:
	DynamicArray(Array<T> array)
		: Array<T>(std::move(array)), size_(capacity())
	{
		if (capacity() == 0)
			*this = Array{0};
	}

	DynamicArray(std::initializer_list<T> list)
		: DynamicArray(Array<T>(list))
	{}

	void reallocate(size_t new_size)
	{
		const size_t size = size_;
		*this = std::move(Array<T>(*this, new_size));
		size_ = size;
	}

	void free_extra_memory()
	{
		if (size_ == capacity())
			return;
		reallocate(size_);
	}

	void append(T element)
	{
		if (size_ >= capacity()) {
			reallocate(capacity()*2);
		}

		(*this)[size_] = std::move(element);
		size_++;
	}

	T& operator[](size_t index) override
	{
		if (index >= size_)
			throw std::out_of_range("Index is out of range");
		return Array<T>::operator[](index);
	}

	const T& operator[](size_t index) const override
	{
		if (index >= size_)
			throw std::out_of_range("Index is out of range");
		return Array<T>::operator[](index);
	}

	T pop(size_t index) override
	{
		for (size_t i = index+1; i < size_; i++)
		{
			(*this)[i - 1] = (*this)[i];
		}
		size_--;

		return (*this)[size_];
	}

	void clear()
	{
		size_ = 0;
	}

	const size_t& capacity() const
	{
		return Array<T>::size();
	}

	const size_t& size() const override
	{
		return size_;
	}

	bool is_empty() const
	{
		return size_ == 0;
	}
private:
	size_t size_;
};

#endif