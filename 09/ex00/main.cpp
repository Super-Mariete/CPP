#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error. Usage: ./btc <input_file>" << std::endl;
		return 1;
	}
	try
	{
		BitcoinExchange btc("data.csv");
		btc.evaluate(argv[1]);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
