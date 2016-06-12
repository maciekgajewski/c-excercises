#include "list.h"

#include <cassert>
#include <iostream>


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
	
	// front
	l.push_front(50); l.push_front(40); l.push_front(3); l.push_front(20); l.push_front(1);
	assert(l.size() == 5);
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
	
	// erase
	l.erase(l.begin());
	assert(l.size() == 4);
	i = 1;
	for (int& x : l)
	{
		assert(x == ++i * 10);
	}
	assert(i == 5);
	
	Karun::List<int>::iterator b = l.begin();
	++b; ++b;
	l.erase(b);
	assert(l.size() == 3);
	i = 1;
	for (int& x : l)
	{
		assert(++i < 4 ? x == i * 10 : x == (i + 1) * 10);
	}
	assert(i == 4);
}

int main()
{
	std::cout << "Testing Karun::List..." << std::endl;
	list_test();
	std::cout << "Tests pass :)" << std::endl;
}