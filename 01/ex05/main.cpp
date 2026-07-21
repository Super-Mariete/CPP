#include "Harl.hpp"
#include <iostream>

int main(void)
{
	Harl harl;

	std::cout << "=== Testing Harl complaints ===" << std::endl;
	std::cout << std::endl;

	harl.complain("DEBUG");
	std::cout << std::endl;

	harl.complain("INFO");
	std::cout << std::endl;

	harl.complain("WARNING");
	std::cout << std::endl;

	harl.complain("ERROR");
	std::cout << std::endl;

	harl.complain("INVALID");

	return 0;
}
