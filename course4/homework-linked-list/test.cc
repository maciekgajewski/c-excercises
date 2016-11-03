#include "linked_list.hh"

#include <cassert>
#include <sstream>
#include <iostream>
#include <forward_list>
#include <algorithm>
#include <numeric>

template<typename LinkedListType>
void test()
{
	// Default construction
	LinkedListType linked_list;
	
	// default created object is empty
	assert(linked_list.empty());

	// push_front and pop_front, empty and front
	int i1 = 5;
	int i2 = 6;
	linked_list.push_front(i1);
	assert(!linked_list.empty());
	assert(linked_list.front()==i1);
	linked_list.pop_front();
	assert(linked_list.empty());

	linked_list.push_front(i1);
	linked_list.push_front(i2);
	assert(!linked_list.empty());
	assert(linked_list.front()==i2);
	linked_list.pop_front();
	assert(!linked_list.empty());
	assert(linked_list.front()==i1);
	linked_list.pop_front();
	assert(linked_list.empty());

	//std::count
	assert(std::count(linked_list.begin(), linked_list.end(), i1) == 0);
	linked_list.push_front(i1);
	linked_list.push_front(i2);
	assert(std::count(linked_list.begin(), linked_list.end(), i1) == 1);
	linked_list.push_front(i1);
	assert(std::count(linked_list.begin(), linked_list.end(), i1) == 2);

	//std::count_if
	assert(std::count_if(linked_list.begin(), linked_list.end(), [&](int n){return n<i2;}) == ((i1<i2)?2:0) );
	assert(std::count_if(linked_list.begin(), linked_list.end(), [&](int n){return n>std::max(i1, i2);}) == 0);

	//for loop iteration
	int sum = 0;
	for (auto it: linked_list)
		sum += it;
	assert(sum == 2*i1 + i2);
	//for loop on empty list
	LinkedListType empty;
	for (auto it: empty)
		assert(false);

	//std::find_if
	assert(*std::find_if(linked_list.begin(), linked_list.end(), [&](int n){return n>=i1;}) == i1);
	assert(std::find_if(linked_list.begin(), linked_list.end(), [&](int n){return n>=i1;}) == linked_list.begin());
	assert(*std::find_if(linked_list.begin(), linked_list.end(), [&](int n){return n>=i2;}) == ((i2>i1)?i2:i1));
	assert(std::find_if(linked_list.begin(), linked_list.end(), [&](int n){return n>std::max(i1, i2);}) == linked_list.end());
	assert(empty.begin()==empty.end());
	assert(std::find_if(empty.begin(), empty.end(), [&](int n){return n>std::max(i1, i2);}) == empty.end());

	//changing the value in the front of the list
	linked_list.front() = i2;
	assert(linked_list.front() == i2);

	//checking that the container actually copies the elements
	LinkedListType linked_list2;
	for (int i=1; i<=100; i++)
		linked_list2.push_front(i);
	assert(std::accumulate(linked_list2.begin(), linked_list2.end(), 0) == 5050);
}

int main()
{
	std::cout << "Testing std::forward_list..." << std::endl;
	test<std::forward_list<int>>();
	std::cout << "std::forward_list passes" << std::endl;

	std::cout << "Testing course::linked_list..." << std::endl;
	test<course::linked_list<int>>();
	std::cout << "course::linked_list passes" << std::endl;
	
}