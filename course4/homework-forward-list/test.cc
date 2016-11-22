#include "forward_list.hh"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <forward_list>

template<typename ListType>
void test_basic()
{
	ListType list;
	assert(list.empty());
	
	list.push_front(100);
	assert(list.empty() == false);
	assert(list.front() == 100);

	list.push_front(200);
	assert(list.front() == 200);

	list.pop_front();
	assert(list.front() == 100);

	list.pop_front();
	assert(list.empty());
}

template<typename ListType>
void test_iterator() {
	ListType list;
	for (int i = 0; i != 10; i++) list.push_front(i);

	// post-increment
	int i = 9;
	for (auto x = std::begin(list); x != std::end(list); x++) {
		assert(*x == i);
		i--;
	}
	// pre-increment
	i = 9;
	for (auto x = std::begin(list); x != std::end(list); ++x) {
		assert(*x == i);
		i--;
	}
	// range-based loop
	i = 9;
	for (auto x : list) {
		assert(x == i);
		i--;
	}


}

void test_size() {
	course::forward_list<int> list;
	assert(list.size() == 0);

	list.push_front(3);
	list.push_front(5);
	assert(list.size() == 2);

	list.pop_front();
	assert(list.size() == 1);

	list.pop_front();
	assert(list.size() == 0);
}

template<typename ListType>
void test_algorithms()
{
	ListType list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);

	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	
	assert(std::count(list.begin(), list.end(), 3) == 2);

	assert(std::count_if(list.begin(), list.end(), [](int i) { return i % 2 == 1; }) == 4);

	auto val = std::find_if(list.begin(), list.end(), [](int i) { return i > 2; });
	assert(*val == 3);
}

int main()
{
	std::cout << "Testing std::forward_list..." << std::endl;
	test_basic<std::forward_list<int>>();
	test_iterator<std::forward_list<int>>();
	test_algorithms<std::forward_list<int>>();
	std::cout << "std::forward_list passes" << std::endl;

	std::cout << "Testing course::forward_list..." << std::endl;
	test_basic<course::forward_list<int>>();
	test_iterator<course::forward_list<int>>();
	test_algorithms<course::forward_list<int>>();
	test_size();
	std::cout << "course::forward_list passes" << std::endl;
}
