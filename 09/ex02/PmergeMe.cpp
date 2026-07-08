#include "PmergeMe.hpp"
#include <algorithm>
#include <utility>

PmergeMe::~PmergeMe() {}

// =========================================================
// Helpers — Jacobsthal sequence for insertion order
// Starts at t2=3, t3=5, t4=11, t5=21 ... (ti = ti-1 + 2*ti-2)
// =========================================================

static std::vector<int> jacobsthalVec(int limit)
{
	std::vector<int> jac;
	jac.push_back(3);
	if (jac.back() >= limit)
		return jac;
	jac.push_back(5);
	while (jac.back() < limit)
		jac.push_back(jac[jac.size() - 1] + 2 * jac[jac.size() - 2]);
	return jac;
}

static std::deque<int> jacobsthalDeq(int limit)
{
	std::deque<int> jac;
	jac.push_back(3);
	if (jac.back() >= limit)
		return jac;
	jac.push_back(5);
	while (jac.back() < limit)
		jac.push_back(jac[jac.size() - 1] + 2 * jac[jac.size() - 2]);
	return jac;
}

// =========================================================
// Ford-Johnson sort — std::vector
// =========================================================

void PmergeMe::sortVector(std::vector<int>& arr)
{
	int n = static_cast<int>(arr.size());
	if (n <= 1)
		return;

	bool odd = (n % 2 != 0);
	int straggler = odd ? arr[n - 1] : 0;
	int pairCount = n / 2;

	// Step 1: form pairs (winner >= loser)
	std::vector<std::pair<int, int> > pairs;
	pairs.reserve(pairCount);
	for (int i = 0; i < pairCount; i++)
	{
		int a = arr[2 * i], b = arr[2 * i + 1];
		if (a < b) std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
	}

	// Step 2: recursively sort winners
	std::vector<int> winners;
	winners.reserve(pairCount);
	for (int i = 0; i < pairCount; i++)
		winners.push_back(pairs[i].first);
	sortVector(winners);

	// Step 3: reorder pairs to match sorted winners
	std::sort(pairs.begin(), pairs.end());

	// Step 4: build result = [loser_0] + all winners
	std::vector<int> result;
	result.reserve(n);
	result.push_back(pairs[0].second);
	for (int i = 0; i < pairCount; i++)
		result.push_back(pairs[i].first);

	// Step 5: insert remaining losers in Jacobsthal order
	if (pairCount > 1)
	{
		std::vector<int> jac = jacobsthalVec(pairCount);
		int prev = 1;

		for (std::size_t g = 0; g < jac.size(); g++)
		{
			int curr = std::min(jac[g], pairCount);
			// Insert from curr down to prev+1 (1-indexed into pairs)
			for (int idx = curr; idx > prev; idx--)
			{
				int loser  = pairs[idx - 1].second;
				int winner = pairs[idx - 1].first;

				// Locate winner to use as upper bound for binary search
				std::vector<int>::iterator winIt =
					std::find(result.begin(), result.end(), winner);
				std::vector<int>::iterator pos =
					std::lower_bound(result.begin(), winIt, loser);
				result.insert(pos, loser);
			}
			prev = curr;
			if (prev >= pairCount)
				break;
		}
	}

	// Step 6: insert straggler
	if (odd)
	{
		std::vector<int>::iterator pos =
			std::lower_bound(result.begin(), result.end(), straggler);
		result.insert(pos, straggler);
	}

	arr = result;
}

// =========================================================
// Ford-Johnson sort — std::deque
// =========================================================

void PmergeMe::sortDeque(std::deque<int>& arr)
{
	int n = static_cast<int>(arr.size());
	if (n <= 1)
		return;

	bool odd = (n % 2 != 0);
	int straggler = odd ? arr[n - 1] : 0;
	int pairCount = n / 2;

	// Step 1: form pairs
	std::deque<std::pair<int, int> > pairs;
	for (int i = 0; i < pairCount; i++)
	{
		int a = arr[2 * i], b = arr[2 * i + 1];
		if (a < b) std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
	}

	// Step 2: recursively sort winners
	std::deque<int> winners;
	for (int i = 0; i < pairCount; i++)
		winners.push_back(pairs[i].first);
	sortDeque(winners);

	// Step 3: reorder pairs to match sorted winners
	std::sort(pairs.begin(), pairs.end());

	// Step 4: build result = [loser_0] + all winners
	std::deque<int> result;
	result.push_back(pairs[0].second);
	for (int i = 0; i < pairCount; i++)
		result.push_back(pairs[i].first);

	// Step 5: insert remaining losers in Jacobsthal order
	if (pairCount > 1)
	{
		std::deque<int> jac = jacobsthalDeq(pairCount);
		int prev = 1;

		for (std::size_t g = 0; g < jac.size(); g++)
		{
			int curr = std::min(jac[g], pairCount);
			for (int idx = curr; idx > prev; idx--)
			{
				int loser  = pairs[idx - 1].second;
				int winner = pairs[idx - 1].first;

				std::deque<int>::iterator winIt =
					std::find(result.begin(), result.end(), winner);
				std::deque<int>::iterator pos =
					std::lower_bound(result.begin(), winIt, loser);
				result.insert(pos, loser);
			}
			prev = curr;
			if (prev >= pairCount)
				break;
		}
	}

	// Step 6: insert straggler
	if (odd)
	{
		std::deque<int>::iterator pos =
			std::lower_bound(result.begin(), result.end(), straggler);
		result.insert(pos, straggler);
	}

	arr = result;
}
