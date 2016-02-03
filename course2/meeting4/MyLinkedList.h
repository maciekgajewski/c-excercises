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

template<typename T>
class Node
{
	typedef std::shared_ptr<Node<T>> node_ptr;

public:
	Node() {}

	Node(const T& value) {
		setValue(value);
	}

	void setValue(const T& value) {
		mValue = value;
	}
	const T& getValue() const {
		return mValue;
	}
	T& getValue() {
		return mValue;
	}

	const node_ptr next() const {
		return mRight;
	}
	void setNext(const node_ptr n) {
		mRight = n;
	}
	const node_ptr previous() const {
		return mLeft;
	}
	void setPrevious(const node_ptr p) {
		mLeft = p;
	}

private:
	node_ptr mLeft;
	node_ptr mRight;
	T mValue;
};



template<typename T>
class MyLinkedList
{
	typedef std::shared_ptr<Node<T>> node_ptr;

public:

    MyLinkedList<T>() {
    	mFront.reset( new Node<T>() );
    	mBack = mFront; //copy assign
    }
    MyLinkedList<T>(const MyLinkedList<T>&); //TODO
    //MyLinkedList<T>(MyLinkedList<T>); TODO: gives compiler error, no time to look into

    void push_front(const T& element) {
    	if ( mSize == 0 ) {
    		mFront->setValue(element);
    	} else {
    		node_ptr temp( new Node<T>() );
    		//will do copy assignment, increasing shared ownership of new node
    		mFront->setNext(temp);
    		//will do copy assignment, increasing shared ownership of current front node
    		temp->setPrevious(mFront);
    		//copy assignment of new node to front. Ref count of old front decreased by 1, now the new node mLeft ptr is one of the owners
    		mFront = temp;
    		mFront->setValue(element);
    	}
    	mSize++;
    }

    //shouldn't this also return the value of the front in addition to removing it?
    void pop_front() {
    	if ( mSize > 0 ) {
    		if ( mSize > 1 ) {
    			mFront = mFront->previous();
    		}
    		mSize--;
    	}
    }
    std::size_t size() const {return mSize;}

    const T& front() const {
    	if ( mSize == 0 ) {
    		//exception? return null?
    		std::cout << "Throw some exception here" << std::endl;
    		//return NULL; doesn't compile
    	}
    	return mFront->getValue();
    }
    T& front() {
    	if ( mSize == 0 ) {
			std::cout << "Throw some exception here" << std::endl;
		}
    	return mFront->getValue();
    }


    // more advanced:
    void push_back(const T& element) {
		if ( mSize == 0 ) {
			mBack->setValue(element);
		} else {
			node_ptr temp( new Node<T>() );
			mBack->setPrevious(temp);
			temp->setNext(mBack);
			mBack = temp;
			mBack->setValue(element);
		}
		mSize++;
	}

    void pop_back() {
		if ( mSize > 0 ) {
			if ( mSize > 1 ) {
				mBack = mBack->next();
			}
			mSize--;
		}
	}

    T& back() {return mBack->getValue();}
    const T& back() const {return mBack->getValue();}

    // extra:
    // how would you provide access to all elements of the list?

    T& operator[](int i) {
    	//compiler requires a return value, so will leave out the check. How to throw exception?
    	//if ( i >= 0 && i < mSize ) {
		if ( i > int(0.5*mSize) ) {
			Node<T>* temp = mBack.get();
			for ( int j = 0; j < i; j++ ) {
				temp = temp->next().get();
			}
			return temp->getValue();
		} else {
			Node<T>* temp = mFront.get();
			for ( int j = 0; j < i; j++ ) {
				temp = temp->previous().get();
			}
			return temp->getValue();
		}
	}

private:
    node_ptr mFront;
    node_ptr mBack;
    size_t mSize = 0;
};



#endif /* MYLINKEDLIST_H_ */
