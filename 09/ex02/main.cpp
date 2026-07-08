#include <iostream>
#include <vector>
#include <deque>
#include <climits>
#include <cerrno>
#include <cstdlib>
#include <sys/time.h>
#include "PmergeMe.hpp"

static double getTimeMicro()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1e6 + tv.tv_usec;
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	std::vector<int> vec;
	std::deque<int>  deq;

	for (int i = 1; i < argc; i++)
	{
		char* end;
		errno = 0;
		long n = std::strtol(argv[i], &end, 10);
		if (*end != '\0' || errno == ERANGE || n < 1 || n > INT_MAX)
		{
			std::cerr << "Error" << std::endl;
			return 1;
		}
		vec.push_back(static_cast<int>(n));
		deq.push_back(static_cast<int>(n));
	}

	// Before
	std::cout << "Before:";
	for (std::size_t i = 0; i < vec.size(); i++)
		std::cout << " " << vec[i];
	std::cout << std::endl;

	// Sort vector and time it
	double t1 = getTimeMicro();
	PmergeMe::sortVector(vec);
	double t2 = getTimeMicro();

	// Sort deque and time it
	double t3 = getTimeMicro();
	PmergeMe::sortDeque(deq);
	double t4 = getTimeMicro();

	// After
	std::cout << "After: ";
	for (std::size_t i = 0; i < vec.size(); i++)
		std::cout << " " << vec[i];
	std::cout << std::endl;

	std::cout << "Time to process a range of " << vec.size()
		<< " elements with std::vector : " << (t2 - t1) << " us" << std::endl;
	std::cout << "Time to process a range of " << deq.size()
		<< " elements with std::deque  : " << (t4 - t3) << " us" << std::endl;

	return 0;
}
