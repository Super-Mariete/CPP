#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <exception>

class RPN
{
public:
	static int evaluate(const std::string& expr);

	class InvalidExpressionException : public std::exception
	{
	public:
		const char* what() const throw();
	};

private:
	RPN();
	RPN(const RPN&);
	RPN& operator=(const RPN&);
	~RPN();
};

#endif
