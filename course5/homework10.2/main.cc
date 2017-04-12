#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "linked_list.h"

int main(int, char**)
{
	// default construction
	jds::LinkedList<std::string> list;
	// push_front() and front()
	list.push_front(std::string("1"));
	assert(list.front() == "1");
	// push_front(T&&)
	std::string s("foo");
	list.push_front(std::move(s));
	list.push_front("banana");
	// emplace_front
	list.emplace_front(5, 'z');
	assert(list.front() == "zzzzz");
	// size()
	assert(list.size() == 4);
	// check ordering
	char const * expected_order[] = {"zzzzz", "banana", "foo", "1"};
	std::size_t index = 0;
	for (auto it = list.begin(); it != list.end(); ++it, ++index)
	{
		assert(*it == expected_order[index]);
	}

	// copy constructor and copy assignment
	jds::LinkedList<std::string> list_copy(list);
	assert(list_copy == list);
	list_copy = list;
	assert(list_copy == list);
	
	// construct from iterators
	jds::LinkedList<std::string> list_from_it(list.begin(), list.end());
	assert(list_from_it == list);

	// move construction and move assignment
	jds::LinkedList<std::string> list_from_move = std::move(list_from_it);
	assert(list_from_move == list);
	assert(list_from_it.size() == 0);
	assert(!(list_from_it == list));
	assert(list_from_it != list);
	list_from_it = jds::LinkedList<std::string>(list.begin(), list.end());
	list_from_move = std::move(list_from_it);
	assert(list_from_move == list);

	// pop_front()
	list_from_move.pop_front();
	assert(list_from_move.front() == "banana");
	assert(list_from_move.size() == 3);
	// pop_front() from empty list
	for (std::size_t i = 0; i < list_from_move.size() + 5; ++i)
		list_from_move.pop_front();
	assert(list_from_move.size() == 0);

	// std algorithms
	auto max_element = std::max_element(list.begin(), list.end());
	assert(*max_element == "zzzzz");
	std::string everything = std::accumulate(list.begin(), list.end(), std::string());
	assert(everything == "zzzzzbananafoo1");

	return 0;
}
