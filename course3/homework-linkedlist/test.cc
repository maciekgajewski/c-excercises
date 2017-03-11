#include "my_linked_list.h"
#include <list>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <boost/range/algorithm/count.hpp>

template<typename ListType>
void list_test()
{
	// Default construction
	ListType list1;

	// default created object is empty
	assert(list1.empty());
	assert(list1.size() == 0);

	list1.push_front(2);
	assert(!list1.empty());
	assert(list1.size() == 1);

	assert(list1.front() == 2);

	list1.pop_front();
	assert(list1.empty());
	assert(list1.size() == 0);

	list1.push_front(3);
	list1.push_front(4);
	list1.push_front(5);

	typename ListType::iterator it = list1.begin();
	list1.erase(it);
	assert(list1.front() == 4);

	list1.push_front(6);

	assert(list1.size() == 3);
	it = list1.begin();
	++it;
	list1.erase(it);
	assert(list1.size() == 2);
	assert(list1.front() == 6);
	list1.pop_front();
	assert(list1.front() == 3);

	ListType list2 = {1,2,3};

	std::for_each(list2.begin(), list2.end(), [](int &i){i++;});
	assert(list2.front() == 2);

	ListType list3 = {4};
	auto result = std::find_first_of(list2.begin(), list2.end(), list3.begin(), list3.end());
	assert(result != list2.end());
	assert(*result == 4);

	std::copy(list2.begin(), list2.end(), std::front_inserter(list3));
	assert(list3.front() == 4);

	std::fill_n(std::front_inserter(list2), 2, -1);
	assert(list2.front() == -1);

	assert(boost::count(list3, 4) == 2);
}

int main()
{
	// test fior std::string - works
	std::cout << "Testing std::list<int>..." << std::endl;
	list_test<std::list<int>>();
	std::cout << "std::list test passes" << std::endl;
	
	std::cout << "Testing MyLinkedList..." << std::endl;
	list_test<MyLinkedList<int>>();
	std::cout << "MyLinkedList test passes" << std::endl;
}
