/*
 * list_test.cc
 *
 *  Created on: Feb 3, 2016
 *      Author: matthijs
 */
#include <cassert>
#include <iostream>
#include "MyLinkedList.h"

int main() {
	MyLinkedList<int> l;
	l.push_front(5);
	assert(l.front() == 5);
	assert(l.back() == 5);
	assert(l[0] == 5);

	l.push_front(10);
	assert(l.front() == 10);
	assert(l.back() == 5);
	assert(l.size() == 2);
	assert(l[0] == 10);
	assert(l[1] == 5);

	l.pop_front();
	assert(l.front() == 5);
	assert(l.back() == 5);
	assert(l.size() == 1);
	assert(l[0] == 5);

	l.pop_front();
	assert(l.size() == 0);
	std::cout << "test passed" << std::endl;
}


