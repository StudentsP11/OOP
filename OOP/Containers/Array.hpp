#ifndef ARRAY_H
#define ARRAY_H

#include <algorithm>
#include <optional>

#include "ISequence.hpp"

template <typename T>
class Array : public ISequence<T>
{
public:
	Array(std::initializer_list<T> list)
		: size_(list.size()),
		pointer_(new T[size_]{})
	{
		size_t i = 0;
		for (const T& element : list)
		{
			if (i >= size_)
				break;
			pointer_[i] = element;
			i++;
		}
	}

	Array(const T array[],
		const size_t new_size,
		const size_t argument_size)
		: size_(new_size), pointer_(new T[new_size]{})
	{
		const size_t min_size = std::min(
			argument_size,
			new_size
		);
		for (size_t i = 0; i < min_size; i++) {
			pointer_[i] = array[i];
		}
	}

	Array(const Array& another)
		: Array(another.pointer_, another.size())
	{}

	Array(const Array& another, size_t new_size)
		: Array(another.pointer_, new_size, another.size())
	{}

	Array& operator=(const Array& another)
	{
		if (&another == this)
			return *this;
		
		Array copy(another);
		std::swap(size_, copy.size_);
		std::swap(pointer_, copy.pointer_);

		return *this;
	}

	Array(Array&& another) noexcept
		: size_(std::exchange(another.size_, 0ull)),
		pointer_(std::exchange(another.pointer_, nullptr))
	{}

	Array& operator=(Array&& another) noexcept
	{
		if (&another == this)
			return *this;

		delete[] pointer_;
		
		size_ = std::exchange(another.size_, 0ull);
		pointer_ = std::exchange(another.pointer_, nullptr);

		return *this;
	}

	~Array() override
	{
		delete[] pointer_;
	}

	T& operator[](size_t index) override
	{
		if (index >= size_)
			throw std::out_of_range("Index is out of range");
		return pointer_[index];
	}

	const T& operator[](size_t index) const override
	{
		if (index >= size_)
			throw std::out_of_range("Index is out of range");
		return pointer_[index];
	}

	T* begin() const
	{
		return pointer_;
	}

	virtual T* end() const
	{
		return pointer_+size_;
	}

	// getter / accessor
	const size_t& size() const override
	{
		return size_;
	}
private:
	size_t size_;
	T* pointer_;

	Array(const T array[],
		const size_t size)
		: size_(size), pointer_(new T[size])
	{
		for (size_t i = 0; i < size; i++)
			pointer_[i] = array[i];
	}
};
#endif