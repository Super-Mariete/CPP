#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp"

int main()
{
	std::vector<int> vec;
	for (int i = 0; i < 10; i++)
		vec.push_back(i * 5);

	// Found
	try {
		std::vector<int>::iterator it = easyfind(vec, 25);
		std::cout << "Found in vector: " << *it << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	// Not found
	try {
		easyfind(vec, 99);
	}
	catch (const std::exception& e) {
		std::cerr << "Vector: " << e.what() << std::endl;
	}

	// List
	std::list<int> lst;
	lst.push_back(3);
	lst.push_back(7);
	lst.push_back(42);

	try {
		std::list<int>::iterator it = easyfind(lst, 42);
		std::cout << "Found in list: " << *it << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	try {
		easyfind(lst, 1);
	}
	catch (const std::exception& e) {
		std::cerr << "List: " << e.what() << std::endl;
	}

	return 0;
}
