#include "my_linked_list.h"
#include <iostream>
#include <cstdlib>
#include <memory>

MyLinkedList::MyLinkedList() : numNodes(0) {
	std::cout << "Default constructor" << std::endl;
}

void MyLinkedList::push_front(const int& value) {
	std::unique_ptr<Node> newHead = std::make_unique<Node>(value);
	newHead->next = std::move(mHead);
	mHead = std::move(newHead);
	numNodes++;
}

void MyLinkedList::pop_front() {
	mHead = std::move(mHead->next);
	numNodes--;
}

std::size_t MyLinkedList::size() const {
	return numNodes;
}

bool MyLinkedList::empty() const {
	return mHead == nullptr;
}
