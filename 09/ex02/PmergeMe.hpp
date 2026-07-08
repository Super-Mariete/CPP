#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>

class PmergeMe
{
public:
	static void sortVector(std::vector<int>& arr);
	static void sortDeque(std::deque<int>& arr);

private:
	PmergeMe();
	PmergeMe(const PmergeMe&);
	PmergeMe& operator=(const PmergeMe&);
	~PmergeMe();
};

#endif
