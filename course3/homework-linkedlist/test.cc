#include "my_linked_list.h"
#include <list>
#include <iostream>
#include <cassert>

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
	for (auto elt : list2)
		std::cout << elt << std::endl;
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
