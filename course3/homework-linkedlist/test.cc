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

	list1.pop_front();
	assert(list1.empty());
	assert(list1.size() == 0);
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
