#include "RPN.hpp"
#include <stack>
#include <sstream>
#include <cctype>

int RPN::evaluate(const std::string& expr)
{
	std::stack<int> stack;
	std::istringstream iss(expr);
	std::string token;

	while (iss >> token)
	{
		if (token.size() == 1 && std::isdigit(token[0]))
		{
			stack.push(token[0] - '0');
		}
		else if (token == "+" || token == "-" || token == "*" || token == "/")
		{
			if (stack.size() < 2)
				throw InvalidExpressionException();
			int b = stack.top(); stack.pop();
			int a = stack.top(); stack.pop();

			if (token == "+")      stack.push(a + b);
			else if (token == "-") stack.push(a - b);
			else if (token == "*") stack.push(a * b);
			else
			{
				if (b == 0)
					throw InvalidExpressionException();
				stack.push(a / b);
			}
		}
		else
		{
			throw InvalidExpressionException();
		}
	}

	if (stack.size() != 1)
		throw InvalidExpressionException();
	return stack.top();
}

const char* RPN::InvalidExpressionException::what() const throw()
{
	return "Error";
}

RPN::~RPN() {}
