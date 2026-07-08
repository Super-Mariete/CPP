#include <iostream>
#include "Array.hpp"

int main()
{
	// Default constructor
	Array<int> empty;
	std::cout << "Empty array size: " << empty.size() << std::endl;

	// Constructor with size
	Array<int> ints(5);
	for (unsigned int i = 0; i < ints.size(); i++)
		ints[i] = static_cast<int>(i * 10);

	std::cout << "Int array: ";
	for (unsigned int i = 0; i < ints.size(); i++)
		std::cout << ints[i] << " ";
	std::cout << std::endl;

	// Copy constructor (deep copy)
	Array<int> copy(ints);
	copy[0] = 999;
	std::cout << "Original[0]: " << ints[0] << " | Copy[0]: " << copy[0] << std::endl;

	// Assignment (deep copy)
	Array<int> assigned;
	assigned = ints;
	assigned[1] = 888;
	std::cout << "Original[1]: " << ints[1] << " | Assigned[1]: " << assigned[1] << std::endl;

	// String array
	Array<std::string> strs(3);
	strs[0] = "hello";
	strs[1] = "world";
	strs[2] = "!";
	std::cout << "String array: ";
	for (unsigned int i = 0; i < strs.size(); i++)
		std::cout << strs[i] << " ";
	std::cout << std::endl;

	// Out of bounds
	try {
		std::cout << ints[10] << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
