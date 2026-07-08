#include "ScalarConverter.hpp"
#include <iostream>
#include <string>
#include <climits>
#include <cfloat>
#include <cstdlib>
#include <cerrno>
#include <cmath>

// ---- Type detection helpers ----

static bool isCharLiteral(const std::string& s)
{
	bool correctLength  = s.length() == 3;
	bool hasOpenQuote   = s[0] == '\'';
	bool hasCloseQuote  = s[2] == '\'';
	return correctLength && hasOpenQuote && hasCloseQuote;
}

static bool isSpecial(const std::string& s)
{
	return s == "nan" || s == "nanf"
		|| s == "+inf" || s == "-inf"
		|| s == "+inff" || s == "-inff"
		|| s == "inf" || s == "inff";
}

static bool isFloat(const std::string& s)
{
	if (s.empty() || s[s.length() - 1] != 'f')
		return false;
	std::string sub = s.substr(0, s.length() - 1);
	char* end;
	errno = 0;
	strtod(sub.c_str(), &end);
	bool fullyParsed    = *end == '\0';
	bool hasDecimalPoint = sub.find('.') != std::string::npos;
	return fullyParsed && hasDecimalPoint;
}

static bool isDouble(const std::string& s)
{
	char* end;
	errno = 0;
	strtod(s.c_str(), &end);
	bool fullyParsed     = *end == '\0';
	bool hasDecimalPoint = s.find('.') != std::string::npos;
	return fullyParsed && hasDecimalPoint;
}

static bool isInt(const std::string& s)
{
	char* end;
	errno = 0;
	long val = strtol(s.c_str(), &end, 10);
	(void)val;
	return !s.empty() && *end == '\0';
}

// ---- Print helpers ----

static void printChar(double d)
{
	if (std::isnan(d) || std::isinf(d) || d < 0 || d > 127)
		std::cout << "char: impossible" << std::endl;
	else if (d < 32 || d == 127)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
}

static void printInt(double d)
{
	if (std::isnan(d) || std::isinf(d)
		|| d > static_cast<double>(INT_MAX) || d < static_cast<double>(INT_MIN))
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(d) << std::endl;
}

static void printFloat(double d)
{
	float f = static_cast<float>(d);
	std::cout << "float: " << f;
	if (!std::isnan(f) && !std::isinf(f) && f == std::floor(f))
		std::cout << ".0";
	std::cout << "f" << std::endl;
}

static void printDouble(double d)
{
	std::cout << "double: " << d;
	if (!std::isnan(d) && !std::isinf(d) && d == std::floor(d))
		std::cout << ".0";
	std::cout << std::endl;
}

// ---- Main convert ----

void ScalarConverter::convert(const std::string& literal)
{
	double d;

	if (isCharLiteral(literal))
	{
		d = static_cast<double>(literal[1]);
	}
	else if (isSpecial(literal))
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;

		if (literal == "nan" || literal == "nanf")
		{
			std::cout << "float: nanf" << std::endl;
			std::cout << "double: nan" << std::endl;
		}
		else if (literal == "+inf" || literal == "+inff" || literal == "inf" || literal == "inff")
		{
			std::cout << "float: +inff" << std::endl;
			std::cout << "double: +inf" << std::endl;
		}
		else
		{
			std::cout << "float: -inff" << std::endl;
			std::cout << "double: -inf" << std::endl;
		}
		return;
	}
	else if (isFloat(literal))
	{
		d = strtod(literal.substr(0, literal.length() - 1).c_str(), NULL);
	}
	else if (isDouble(literal))
	{
		d = strtod(literal.c_str(), NULL);
	}
	else if (isInt(literal))
	{
		d = static_cast<double>(strtol(literal.c_str(), NULL, 10));
	}
	else if (literal.length() == 1)
	{
		d = static_cast<double>(literal[0]);
	}
	else
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}

	printChar(d);
	printInt(d);
	printFloat(d);
	printDouble(d);
}
