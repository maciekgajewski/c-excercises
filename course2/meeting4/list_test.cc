/*
 * list_test.cc
 *
 *  Created on: Feb 3, 2016
 *      Author: matthijs
 */
#include <vector>
#include <numeric>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <iterator>
#include "MyLinkedList.h"

static const int NUM = 10;

void mytests() {
	MyLinkedList<int> l;
	l.push_front(5);
	assert(l.front() == 5);
	assert(l.back() == 5);

	l.push_front(10);
	assert(l.front() == 10);
	assert(l.back() == 5);
	assert(l.size() == 2);

	MyLinkedList<int> copiedList(l);
	assert(copiedList.front() == 10);
	assert(copiedList.back() == 5);
	assert(copiedList.size() == 2);

	l.pop_front();
	assert(l.front() == 5);
	assert(l.back() == 5);
	assert(l.size() == 1);
	assert(copiedList.front() == 10);
	assert(copiedList.back() == 5);
	assert(copiedList.size() == 2);

	l.push_back(15);
	assert(l.front() == 5);
	assert(l.back() == 15);
	assert(l.size() == 2);

	l.pop_back();
	assert(l.front() == 5);
	assert(l.back() == 5);
	assert(l.size() == 1);

	l.pop_front();
	assert(l.size() == 0);
}

template<typename MyLinkedList>
void Populate(MyLinkedList& l)
{
	std::vector<int> vec(NUM);
	std::iota(vec.begin(), vec.end(), 0); // fill vector with 0 .. 9

	// copy from vector to list
	l.clear();
	assert(l.empty());
	std::copy(vec.begin(), vec.end(), std::front_inserter(l));
	assert(l.size() == NUM);
}

template<typename MyLinkedList>
void Verify(const MyLinkedList& l)
{
	assert(l.size() == NUM);

	int first = l.front();
	int sum = std::accumulate(l.begin(), l.end(), 0);

	assert(first == 9);
	assert(sum == 45);
}

void bla(MyLinkedList<int>& l)
{
	std::vector<int> vec(NUM);
	std::iota(vec.begin(), vec.end(), 0); // fill vector with 0 .. 9

	// copy from vector to list
	l.clear();
	assert(l.empty());
	std::copy(vec.begin(), vec.end(), std::front_inserter(l));
	assert(l.size() == NUM);
}

int main()
{
	MyLinkedList<int> l;

	bla(l);
	Verify(l);
	mytests();
	std::cout << "tests passed" << std::endl;
}



