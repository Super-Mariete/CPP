#include <iostream>
#include <string>
#include "iter.hpp"

template <typename T>
void print(const T& x)
{
	std::cout << x << std::endl;
}

template <typename T>
void doubleIt(T& x)
{
	x *= 2;
}

int main()
{
	int arr[] = {1, 2, 3, 4, 5};
	std::cout << "Ints:" << std::endl;
	::iter(arr, 5, print<int>);

	::iter(arr, 5, doubleIt<int>);
	std::cout << "Doubled:" << std::endl;
	::iter(arr, 5, print<int>);

	std::string words[] = {"hello", "world", "templates"};
	std::cout << "Strings:" << std::endl;
	::iter(words, 3, print<std::string>);

	return 0;
}
