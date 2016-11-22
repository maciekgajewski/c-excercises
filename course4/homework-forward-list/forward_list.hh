#pragma once

#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>

namespace course {

template<typename T>
struct forward_list_node
{
	forward_list_node(const T& value, std::unique_ptr<forward_list_node<T>> next)
		: value(value), next(std::move(next)) { }

	const T value;
	std::unique_ptr<forward_list_node<T>> next;
};

template<typename T>
class forward_list_iterator: public std::iterator<std::forward_iterator_tag, T>
{
public:
	forward_list_iterator(forward_list_node<T>* mStart) : mCurrent(mStart) {}

	const T& operator*() const {
		return mCurrent->value;
	}
	T& operator->() const {
		return mCurrent->value;
	}
	forward_list_iterator& operator++() {
		mCurrent = mCurrent->next.get();
		return *this;
	}
	forward_list_iterator operator++(int) {
		forward_list_node<T>* current = mCurrent;
		mCurrent = mCurrent->next.get();
		return current;
	}
	bool operator !=(const forward_list_iterator& other) const {
		return mCurrent != other.mCurrent;
	}
	bool operator ==(const forward_list_iterator& other) const {
		return mCurrent == other.mCurrent;
	}
private:
	forward_list_node<T>* mCurrent;
};



template<typename T>
class forward_list
{
public:
	forward_list() 
		: mSize(0), mFront(nullptr) {}

	bool empty() const {
		return mSize == 0;
	}
	std::size_t size() const {
		return mSize;
	}
	const T front() const {
		return mFront->value;
	}
	void pop_front() {
		if (mSize == 0) return;
		mFront = std::move(mFront->next);
		mSize -= 1;
	}
	void push_front(const T& value) {
		mFront = std::make_unique<forward_list_node<T>>(value, std::move(mFront));
		mSize += 1;
	}
	void push_front(T&& value) {
		mFront = std::make_unique<forward_list_node<T>>(std::move(value), std::move(mFront));
		mSize += 1;
	}

	forward_list_iterator<T> begin() {
		return forward_list_iterator<T>(mFront.get());
	}
	forward_list_iterator<T> end() {
		return forward_list_iterator<T>(nullptr);
	}
	const forward_list_iterator<T> begin() const {
		return begin();
	}
	const forward_list_iterator<T> end() const {
		return end();
	}
private:
	std::size_t mSize;
	std::unique_ptr<forward_list_node<T>> mFront;
};

}
