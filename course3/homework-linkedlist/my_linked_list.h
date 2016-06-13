#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>

template<typename T>
class MyLinkedList {
	struct Node {
		T mData;
		std::unique_ptr<Node> mNext;
		Node(const T& value) : mData(value) {}
	};

	public:
	class iterator {
		public:
			Node* mPtr = nullptr;
			iterator(Node* node) : mPtr(node) {}
			bool operator==(const iterator& it) {
				return mPtr == it.mPtr;
			}
			bool operator!=(const iterator& it) {
				return !operator==(it);
			}
			iterator& operator++() {
				mPtr = mPtr->mNext.get();
				return *this;
			}
			T& operator*() {
				return mPtr->mData;
			}
	};

	class const_iterator
	{
		public:
			Node* mPtr = nullptr;
			const_iterator(const iterator& it) : mPtr(it.mPtr) {}
			const_iterator(Node* node) : mPtr(node) {}

			bool operator==(const const_iterator& it) {
				return mPtr == it.mPtr;
			}
			bool operator!=(const const_iterator& it) {
				return !operator==(it);
			}
			const_iterator& operator++() {
				mPtr = mPtr->mNext.get();
				return *this;
			}
			const T& operator*() {
				return mPtr->mData;
			}
	};

	std::size_t size() const {
		return numNodes;
	}

	bool empty() const {
		return mHead == nullptr;
	}

	MyLinkedList() : numNodes(0) {}

	MyLinkedList(std::initializer_list<T> initList) {
		numNodes = initList.size();
		for (auto reverseIterator = std::rbegin(initList); reverseIterator != std::rend(initList); ++reverseIterator)
			push_front(*reverseIterator);
	}

	void push_front(const T& value) {
		std::unique_ptr<Node> newHead = std::make_unique<Node>(value);
		newHead->mNext = std::move(mHead);
		mHead = std::move(newHead);
		numNodes++;
	}

	void pop_front() {
		mHead = std::move(mHead->mNext);
		numNodes--;
	}

	const T& front() const {
		return mHead->mData;
	}

	T& front() {
		return mHead->mData;
	}

	const_iterator begin() const {
		return mHead.get();
	}

	iterator begin() {
		return mHead.get();
	}

	const_iterator end() const {
		return nullptr;
	}

	iterator end() {
		return nullptr;
	}

	void erase(iterator toErase) {
		if (toErase == begin()) {
			pop_front();
			return;
		}

		for (iterator it = begin(); it != end(); ++it) {
			if (it.mPtr->mNext.get() == toErase.mPtr) {
				it.mPtr->mNext = std::move(toErase.mPtr->mNext);
				numNodes--;
				break;
			}
		}
	}
	private:
	std::size_t numNodes;
	std::unique_ptr<Node> mHead;
};
