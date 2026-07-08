#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include <cstdlib>

BitcoinExchange::BitcoinExchange(const std::string& dbFile)
{
	std::ifstream file(dbFile.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open database.");

	std::string line;
	std::getline(file, line); // skip header

	while (std::getline(file, line))
	{
		std::size_t comma = line.find(',');
		if (comma == std::string::npos)
			continue;
		std::string date = line.substr(0, comma);
		float rate = static_cast<float>(std::atof(line.substr(comma + 1).c_str()));
		_rates[date] = rate;
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _rates(other._rates) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_rates = other._rates;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7) continue;
		if (!std::isdigit(date[i]))
			return false;
	}
	int month = std::atoi(date.substr(5, 2).c_str());
	int day   = std::atoi(date.substr(8, 2).c_str());
	return month >= 1 && month <= 12 && day >= 1 && day <= 31;
}

bool BitcoinExchange::isValidValue(const std::string& str, float& out) const
{
	char* end;
	double val = std::strtod(str.c_str(), &end);
	if (*end != '\0')
	{
		std::cout << "Error: bad input => " << str << std::endl;
		return false;
	}
	if (val < 0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return false;
	}
	if (val > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return false;
	}
	out = static_cast<float>(val);
	return true;
}

void BitcoinExchange::evaluate(const std::string& inputFile) const
{
	std::ifstream file(inputFile.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line); // skip header "date | value"

	while (std::getline(file, line))
	{
		std::size_t sep = line.find(" | ");
		if (sep == std::string::npos)
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date     = line.substr(0, sep);
		std::string valueStr = line.substr(sep + 3);

		if (!isValidDate(date))
		{
			std::cout << "Error: bad input => " << date << std::endl;
			continue;
		}

		float value;
		if (!isValidValue(valueStr, value))
			continue;

		// Find closest date <= given date
		std::map<std::string, float>::const_iterator it = _rates.upper_bound(date);
		if (it == _rates.begin())
		{
			std::cout << "Error: bad input => " << date << std::endl;
			continue;
		}
		--it;

		std::cout << date << " => " << value << " = " << value * it->second << std::endl;
	}
}
