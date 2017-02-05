/*
 * MyLinkedList.h
 *
 *  Created on: Feb 3, 2016
 *      Author: matthijs
 */

#ifndef MYLINKEDLIST_H_
#define MYLINKEDLIST_H_

#include <iostream>
#include <memory>
#include <algorithm>
#include <iterator>

template<typename T>
struct Node
{
	T mValue;
	Node* mPrev;
	std::unique_ptr<Node> mNext;
};

template<typename T>
class ListIterator
{
public:
	//These are necessary in order to use std::copy in line 60
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef std::ptrdiff_t difference_type;
	typedef std::forward_iterator_tag iterator_category;

	ListIterator(Node<T>* c) : mCurrent(c) { }

	T& operator*() { return mCurrent->mValue; }
	void operator++() { mCurrent = mCurrent->mNext.get(); }
	bool operator!=(const ListIterator& o) const
	{
		return mCurrent != o.mCurrent;
	}

private:
	Node<T>* mCurrent = nullptr;
};

template<typename T>
class MyLinkedList
{

public:

	typedef std::unique_ptr<Node<T>> node_ptr;
	typedef T value_type;

	MyLinkedList<T>() {}

    MyLinkedList<T>(const MyLinkedList<T>& oldList) {
    	std::copy(oldList.begin(), oldList.end(), std::front_inserter(*this));
    }

    std::size_t size() const {return mSize;}

    void push_front(const T& element) {
		if ( mSize > 0 ) {
			node_ptr newNode( new Node<T>{element} );
			newNode->mPrev = mFront;
			mFront = newNode.get();
			mFront->mPrev->mNext = std::move(newNode);
		} else {
			mBack = node_ptr( new Node<T>{element} );
			mFront = mBack.get();
		}
    	mSize++;
    }

    void pop_front() {
		if ( mSize > 1 ) {
			mFront = mFront->mPrev;
			mFront->mNext.reset();
		} else {
			mBack.reset();
		}
		mSize = mSize == 0 ? 0 : mSize-1;
    }

    const T& front() const {
    	//I'm gonna stick to std::list API: "Calling front on an empty container is undefined."
    	return mFront->mValue;
    }
    T& front() {
    	return mFront->mValue;
    }

    void push_back(const T& element) {
		if ( mSize > 0 ) {
			node_ptr newNode( new Node<T>{element} );
			mBack->mPrev = newNode.get();
			newNode->mNext = std::move(mBack);
			mBack = std::move(newNode);
		} else {
			mBack = node_ptr( new Node<T>{element} );
			mFront = mBack.get();
		}
		mSize++;
	}

	void pop_back() {
		if ( mSize > 1 ) {
			mBack = std::move(mBack->mNext);
		} else {
			mBack.reset();
		}
		mSize = mSize == 0 ? 0 : mSize-1;
	}

	const T& back() const {
		return mBack->mValue;
	}
	T& back() {
		return mBack->mValue;
	}

	void clear() {
		mBack.reset();
		mSize = 0;
	}

	bool empty() const {
		return mSize == 0;
	}

	ListIterator<T> begin() const {
		return ListIterator<T>(mBack.get());
	}

	ListIterator<T> end() const {
		return ListIterator<T>(nullptr);
	}


private:
    //need to use raw pointer for front, otherwise need shared pointer
    Node<T>* mFront = nullptr;
    node_ptr mBack;
    size_t mSize = 0;
};



#endif /* MYLINKEDLIST_H_ */
