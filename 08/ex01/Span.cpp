#include "Span.hpp"
#include <algorithm>
#include <climits>

Span::Span(unsigned int n) : _maxSize(n) {}

Span::Span(const Span& other) : _maxSize(other._maxSize), _data(other._data) {}

Span& Span::operator=(const Span& other)
{
	if (this != &other)
	{
		_maxSize = other._maxSize;
		_data = other._data;
	}
	return *this;
}

Span::~Span() {}

void Span::addNumber(int n)
{
	if (_data.size() >= _maxSize)
		throw FullException();
	_data.push_back(n);
}

int Span::shortestSpan() const
{
	if (_data.size() < 2)
		throw NotEnoughNumbersException();

	std::vector<int> sorted(_data);
	std::sort(sorted.begin(), sorted.end());

	int shortest = INT_MAX;
	for (std::size_t i = 1; i < sorted.size(); i++)
	{
		int diff = sorted[i] - sorted[i - 1];
		if (diff < shortest)
			shortest = diff;
	}
	return shortest;
}

int Span::longestSpan() const
{
	if (_data.size() < 2)
		throw NotEnoughNumbersException();

	int minVal = *std::min_element(_data.begin(), _data.end());
	int maxVal = *std::max_element(_data.begin(), _data.end());
	return maxVal - minVal;
}

const char* Span::FullException::what() const throw()
{
	return "Span is full";
}

const char* Span::NotEnoughNumbersException::what() const throw()
{
	return "Not enough numbers to compute a span";
}
