#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <stdexcept>

class Span
{
public:
	Span(unsigned int n);
	Span(const Span& other);
	Span& operator=(const Span& other);
	~Span();

	void			addNumber(int n);

	template <typename Iterator>
	void			addRange(Iterator begin, Iterator end)
	{
		if (_data.size() + (std::size_t)std::distance(begin, end) > _maxSize)
			throw FullException();
		_data.insert(_data.end(), begin, end);
	}

	int				shortestSpan() const;
	int				longestSpan() const;

	class FullException : public std::exception
	{
	public:
		const char* what() const throw();
	};

	class NotEnoughNumbersException : public std::exception
	{
	public:
		const char* what() const throw();
	};

private:
	unsigned int		_maxSize;
	std::vector<int>	_data;
};

#endif
