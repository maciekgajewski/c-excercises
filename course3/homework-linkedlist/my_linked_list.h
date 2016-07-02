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
	typedef T value_type;
	class iterator : public std::iterator<std::forward_iterator_tag, T> {
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
			iterator operator++(int) {
				return iterator(mPtr->mNext.get());
			}
			T& operator*() {
				return mPtr->mData;
			}
	};

	class const_iterator : public std::iterator<std::forward_iterator_tag, const T>
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
			const_iterator operator++(int) {
				return const_iterator(mPtr->mNext.get());
			}
			const T& operator*() {
				return mPtr->mData;
			}
	};

	std::size_t size() const {
		return mNumNodes;
	}

	bool empty() const {
		return mHead == nullptr;
	}

	MyLinkedList() : mNumNodes(0) {}

	MyLinkedList(std::initializer_list<T> initList) {
		mNumNodes = initList.size();
		for (auto reverseIterator = std::rbegin(initList); reverseIterator != std::rend(initList); ++reverseIterator)
			push_front(*reverseIterator);
	}

	void push_front(const T& value) {
		std::unique_ptr<Node> newHead = std::make_unique<Node>(value);
		newHead->mNext = std::move(mHead);
		mHead = std::move(newHead);
		mNumNodes++;
	}

	void pop_front() {
		mHead = std::move(mHead->mNext);
		mNumNodes--;
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
				mNumNodes--;
				break;
			}
		}
	}
	private:
	std::size_t mNumNodes;
	std::unique_ptr<Node> mHead;
};
