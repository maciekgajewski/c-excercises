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
	
	// initializer list
	l = {50, 40, 3, 20, 1};
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
	l2.push_front(std::make_unique<int>(100));
	i = 0;
	for (auto& u : l2)
	{
		assert(*u == ++i * 100);
	}
}

int main()
{
	std::cout << "Testing Karun::List..." << std::endl;
	list_test();
	std::cout << "Tests pass :)" << std::endl;
}