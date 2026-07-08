#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <stdexcept>
# include <cstddef>

template <typename T>
class Array
{
public:
	Array() : _data(new T[0]()), _size(0) {}

	Array(unsigned int n) : _data(new T[n]()), _size(n) {}

	Array(const Array& other) : _data(new T[other._size]()), _size(other._size)
	{
		for (std::size_t i = 0; i < _size; i++)
			_data[i] = other._data[i];
	}

	Array& operator=(const Array& other)
	{
		if (this != &other)
		{
			delete[] _data;
			_size = other._size;
			_data = new T[_size]();
			for (std::size_t i = 0; i < _size; i++)
				_data[i] = other._data[i];
		}
		return *this;
	}

	~Array() { delete[] _data; }

	T& operator[](std::size_t index)
	{
		if (index >= _size)
			throw std::out_of_range("Index out of bounds");
		return _data[index];
	}

	const T& operator[](std::size_t index) const
	{
		if (index >= _size)
			throw std::out_of_range("Index out of bounds");
		return _data[index];
	}

	unsigned int size() const { return static_cast<unsigned int>(_size); }

private:
	T*			_data;
	std::size_t	_size;
};

#endif
