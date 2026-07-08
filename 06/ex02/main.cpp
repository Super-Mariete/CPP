#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Base.hpp"

int main()
{
	std::srand(std::time(NULL));

	for (int i = 0; i < 6; i++)
	{
		Base* obj = generate();
		std::cout << "Via pointer : ";
		identify(obj);
		std::cout << "Via reference: ";
		identify(*obj);
		std::cout << std::endl;
		delete obj;
	}

	return 0;
}
