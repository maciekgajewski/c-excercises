#pragma once

#include <cstddef>


namespace Karun
{

template<typename T>
class List
{
public:
	class Node
	{
	friend class List;
	
	public:
		Node() = default;
		Node(const Node& node) = default;
		Node(const T& data, Node* next) : mData(data), mNext(next) {}
		
	private:
		T mData;
		Node* mNext = nullptr;
	};
	
	class iterator
	{
	friend class List;
		
	public:
		iterator(Node* node) : mNode(node) {}
		
		bool operator==(const iterator& it) { return mNode == it.mNode; }
		bool operator!=(const iterator& it) { return !operator==(it); }
		iterator& operator++() { mNode = mNode->mNext; return *this; }
		T& operator*() { return mNode->mData; }
		
	private:
		Node* mNode = nullptr;
	};
	
	class const_iterator
	{
	public:
		const_iterator(const iterator& it) : mNode(it.mNode) {}
		const_iterator(Node* node) : mNode(node) {}
		
		bool operator==(const const_iterator& it) { return mNode == it.mNode; }
		bool operator!=(const const_iterator& it) { return !operator==(it); }
		const_iterator& operator++() { mNode = mNode->mNext; return *this; }
		const T& operator*() { return mNode->mData; }
		
	private:
		Node* mNode = nullptr;
	};
	
	~List() { while (size() > 0) pop_front(); }
	
	iterator begin() { return mBegin; }
	const_iterator begin() const { return mBegin; }
	iterator end() { return nullptr; }
	const_iterator end() const { return nullptr; }
	
	bool empty() const { return mSize == 0; }
	std::size_t size() const { return mSize; }
	T& front() { return mBegin->mData; }
	const T& front() const { return mBegin->mData; }
	
	void push_front(const T& data)
	{
		Node* node = new Node(data, mBegin);
		mBegin = node;
		mSize++;
	}
	
	void pop_front()
	{
		Node* node = mBegin;
		mBegin = mBegin->mNext;
		delete node;
		mSize--;
	}
	
	void erase(iterator e)
	{
		iterator it = mBegin;
		if (it == e)
		{
			pop_front();
			return;
		}
		
		while (it.mNode->mNext != e.mNode) { ++it; }
		Node* node = it.mNode->mNext;
		it.mNode->mNext = it.mNode->mNext->mNext;
		delete node;
		mSize--;
	}
	
private:
	std::size_t mSize = 0;
	Node* mBegin = nullptr;
};

}