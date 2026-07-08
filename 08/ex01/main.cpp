#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Span.hpp"

int main()
{
	// Basic test
	Span sp(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
	std::cout << "Longest span:  " << sp.longestSpan() << std::endl;

	// Full exception
	try {
		sp.addNumber(42);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Not enough numbers
	try {
		Span small(1);
		small.addNumber(5);
		small.shortestSpan();
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Large span with addRange
	std::cout << "\nLarge span (10000 numbers):" << std::endl;
	std::srand(std::time(NULL));
	Span large(10000);
	std::vector<int> nums;
	for (int i = 0; i < 10000; i++)
		nums.push_back(std::rand());
	large.addRange(nums.begin(), nums.end());
	std::cout << "Shortest span: " << large.shortestSpan() << std::endl;
	std::cout << "Longest span:  " << large.longestSpan() << std::endl;

	return 0;
}
