#ifndef ISEQUENCE_H
#define ISEQUENCE_H

template <typename T>
class ISequence
{
public:
	virtual T& operator[](size_t index) = 0;
	virtual const T& operator[](size_t index) const = 0;
	virtual const size_t& size() const = 0;

	virtual ~ISequence() = default;
};

template <typename T>
std::ostream& operator<<(
	std::ostream& out,
	const ISequence<T>& array)
{
	out << '[';
	if (array.size() > 0)
	{
		for (size_t i = 0; i < array.size() - 1; i++)
			out << array[i] << ", ";
		out << array[array.size() - 1];
	}
	out << "]\n";

	return out;
}

template <typename T>
class IPushable
{
public:
	virtual void push(T element) = 0;

	virtual ~IPushable() = default;
};

template <typename T>
class IPopable
{
public:
	virtual T pop() = 0;

	virtual ~IPopable() = default;
};

template <typename T>
class IIndexedPopable
{
public:
	virtual T pop(size_t index) = 0;

	virtual ~IIndexedPopable() = default;
};

#endif