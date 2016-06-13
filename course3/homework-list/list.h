#pragma once

#include <memory>
#include <initializer_list>


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
		Node(T data, std::unique_ptr<Node>& next) : mData(std::move(data)), mNext(std::move(next)) {}
		
	private:
		T mData;
		std::unique_ptr<Node> mNext;
	};
	
	class iterator
	{
	friend class List;
		
	public:
		iterator(Node* node) : mNode(node) {}
		
		bool operator==(const iterator& it) { return mNode == it.mNode; }
		bool operator!=(const iterator& it) { return !operator==(it); }
		iterator& operator++() { mNode = mNode->mNext.get(); return *this; }
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
		const_iterator& operator++() { mNode = mNode->mNext.get(); return *this; }
		const T& operator*() { return mNode->mData; }
		
	private:
		Node* mNode = nullptr;
	};
	
	List() = default;
	List(const std::initializer_list<T>& list) { for (const T& t : list) push_front(t); }
	
	iterator begin() { return mBegin.get(); }
	const_iterator begin() const { return mBegin.get(); }
	iterator end() { return nullptr; }
	const_iterator end() const { return nullptr; }
	
	bool empty() const { return mSize == 0; }
	std::size_t size() const { return mSize; }
	
	T& front() { return mBegin->mData; }
	const T& front() const { return mBegin->mData; }
	
	void push_front(T data)
	{
		mBegin = std::make_unique<Node>(std::move(data), mBegin);
		mSize++;
	}
	
	void pop_front()
	{
		mBegin = std::move(mBegin->mNext);
		mSize--;
	}
	
	void erase(iterator it)
	{
		iterator e = begin();
		if (e == it)
		{
			pop_front();
			return;
		}
		
		while (e.mNode->mNext.get() != it.mNode) 
			++e;
		e.mNode->mNext = std::move(e.mNode->mNext->mNext);
		mSize--;
	}
	
private:
	std::size_t mSize = 0;
	std::unique_ptr<Node> mBegin;
};

}