#include "list.h"

#include <cassert>
#include <iostream>
#include <algorithm>
#include <boost/range/algorithm.hpp>


void list_test()
{
	// default constructor
	Karun::List<int> l;
	assert(l.empty());
	assert(l.size() == 0);
	assert(l.begin() == l.end());
	
	// push_front
	l.push_front(10);
	assert(l.size() == 1);
	assert(l.front() == 10);
	l.push_front(20);
	assert(l.size() == 2);
	assert(l.front() == 20);
	l.push_front(30);
	assert(l.size() == 3);
	assert(l.front() == 30);
	
	// pop_front
	l.pop_front();
	assert(l.size() == 2);
	assert(l.front() == 20);
	l.pop_front();
	assert(l.size() == 1);
	assert(l.front() == 10);
	l.pop_front();
	assert(l.empty());
	assert(l.begin() == l.end());
	
	// initializer list
	l = {1, 20, 3, 40, 50};
	assert(l.size() == 5);
	
	// front
	assert(l.front() == 1);
	l.front() *= 10;
	assert(l.front() == 10);
	
	// iterator
	int i = 0;
	for (Karun::List<int>::iterator it = l.begin(); it != l.end(); ++it)
	{
		++i;
		if (i == 3) *it *= 10;
		assert(*it == i * 10);
	}
	assert (i == 5);
	
	// range-based for
	l.front() = 1;
	assert(l.front() == 1);
	i = 0;
	for (int& x : l)
	{
		++i;
		if (i == 1) x *= 10;
		assert(x == i * 10);
	}
	assert(i == 5);
	
	// const_iterator
	i = 0;
	for (Karun::List<int>::const_iterator it = l.begin(); it != l.end(); ++it)
	{
		assert(*it == ++i * 10);
	}
	assert (i == 5);
	
	// erase first element
	l.erase(l.begin());
	assert(l.size() == 4);
	auto b = l.begin();
	assert(*b == 20);
	assert(*++b == 30);
	assert(*++b == 40);
	assert(*++b == 50);
	assert(++b == l.end());
	
	// erase mid element
	l.erase(++++l.begin());
	assert(l.size() == 3);
	b = l.begin();
	assert(*b == 20);
	assert(*++b == 30);
	assert(*++b == 50);
	assert(++b == l.end());
	
	// erase last element
	l.erase(++++l.begin());
	assert(l.size() == 2);
	b = l.begin();
	assert(*b == 20);
	assert(*++b == 30);
	assert(++b == l.end());
	
	// erase all elements
	l.erase(++l.begin());
	assert(l.size() == 1);
	assert(*l.begin() == 20);
	l.erase(l.begin());
	assert(l.empty());
	
	// list of move only objects
	Karun::List<std::unique_ptr<int>> l2;
	l2.push_front(std::make_unique<int>(300));
	l2.push_front(std::make_unique<int>(200));
	std::unique_ptr<int> u1 = std::make_unique<int>(100);
	l2.push_front(std::move(u1));
	i = 0;
	for (auto& u : l2)
	{
		assert(*u == ++i * 100);
	}
	
	// distance
	l = {1, 1, 1, 1, 2, 2, 2, 3, 3, 4};
	assert(std::distance(l.begin(), l.end()) == 10);
	assert(boost::distance(l) == 10);
	
	// count and count_if
	assert(std::count(l.begin(), l.end(), 2) == 3);
	assert(std::count_if(l.begin(), l.end(), [](int n){ return n >= 2; }) == 6);
	assert(boost::count(l, 2) == 3);
	assert(boost::count_if(l, [](int n){ return n >= 2; }) == 6);
	
	// front_inserter
	Karun::List<int> l3 = {1, 2, 3};
	Karun::List<int> l4;
	boost::copy(l3, std::front_inserter(l4));
	b = l4.begin();
	assert(*b == 3);
	assert(*++b == 2);
	assert(*++b == 1);
	assert(++b == l4.end());
	
	// transform
	std::transform(l4.begin(), l4.end(), l4.begin(), [](int n){ return n * n; });
	boost::transform(l4, l4.begin(), [](int n){ return n * n; });
	b = l4.begin();
	assert(*b == 81);
	assert(*++b == 16);
	assert(*++b == 1);
	assert(++b == l4.end());
	
	// move
	Karun::List<std::unique_ptr<int>> l5;
	std::move(l2.begin(), l2.end(), std::front_inserter(l5));
	assert(l2.size() == l5.size());
	for (auto& u : l2)
		assert(!u);
	auto b5 = l5.begin();
	assert(**b5 == 300);
	assert(**++b5 == 200);
	assert(**++b5 == 100);
	assert(++b5 == l5.end());
}

int main()
{
	std::cout << "Testing Karun::List..." << std::endl;
	list_test();
	std::cout << "Tests pass :)" << std::endl;
}
