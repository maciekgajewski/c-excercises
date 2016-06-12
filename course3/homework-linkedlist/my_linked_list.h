#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>

template<typename T>
class MyLinkedList {
	struct Node {
		T data;
		std::unique_ptr<Node> next;
		Node(const T& value) : data(value), next(nullptr) {}
	};

	public:
		std::size_t size() const {
			return numNodes;
		}
		bool empty() const {
			return mHead == nullptr;
		}
		MyLinkedList() : numNodes(0) {
			std::cout << "Default constructor" << std::endl;
		}
		void push_front(const T& value) {
			std::unique_ptr<Node> newHead = std::make_unique<Node>(value);
			newHead->next = std::move(mHead);
			mHead = std::move(newHead);
			numNodes++;
		}
		void pop_front() {
			mHead = std::move(mHead->next);
			numNodes--;
		}

	private:
		std::size_t numNodes;
		std::unique_ptr<Node> mHead;
};
