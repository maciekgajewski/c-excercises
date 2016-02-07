#include <list>
#include <vector>
#include <numeric>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <iterator>

static const int NUM = 10;

template<typename List>
void Populate(List& l)
{
	std::vector<int> v(NUM);
	std::iota(v.begin(), v.end(), 0); // fill vector with 0 .. 9
	
	// copy from vector to list
	l.clear();
	assert(l.empty());
	std::copy(v.begin(), v.end(), std::front_inserter(l));
	assert(l.size() == NUM);
}

template<typename List>
void Verify(const List& l)
{
	assert(l.size() == NUM);
	
	int first = l.front();
	int sum = std::accumulate(l.begin(), l.end(), 0);
	
	assert(first == 9);
	assert(sum == 45);
}

int main()
{
	std::list<int> l;

	Populate(l);
	Verify(l);
}