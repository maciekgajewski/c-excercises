#pragma once

#include <iterator>
#include <memory>
#include <initializer_list>
#include <boost/range/adaptor/reversed.hpp>


namespace Karun
{

template<typename T>
class List
{
public:
	typedef T value_type;
	
	class Node
	{
	friend class List;
	
	public:
		Node(const T& data, std::unique_ptr<Node>& next) : mData(data), mNext(std::move(next)) {}
		Node(T&& data, std::unique_ptr<Node>& next) : mData(std::move(data)), mNext(std::move(next)) {}
		
	private:
		T mData;
		std::unique_ptr<Node> mNext;
	};
	
	class iterator : public std::iterator<std::forward_iterator_tag, T>
	{
	friend class List;
		
	public:
		iterator(Node* node) : mNode(node) {}
		
		bool operator==(const iterator& it) { return mNode == it.mNode; }
		bool operator!=(const iterator& it) { return !operator==(it); }
		iterator& operator++() { mNode = mNode->mNext.get(); return *this; }
		iterator operator++(int) { return iterator(mNode->mNext.get()); }
		T& operator*() { return mNode->mData; }
		
	private:
		Node* mNode = nullptr;
	};
	
	class const_iterator : public std::iterator<std::forward_iterator_tag, const T>
	{
	public:
		const_iterator(const iterator& it) : mNode(it.mNode) {}
		const_iterator(Node* node) : mNode(node) {}
		
		bool operator==(const const_iterator& it) { return mNode == it.mNode; }
		bool operator!=(const const_iterator& it) { return !operator==(it); }
		const_iterator& operator++() { mNode = mNode->mNext.get(); return *this; }
		const_iterator operator++(int) { return const_iterator(mNode->mNext.get()); }
		const T& operator*() { return mNode->mData; }
		
	private:
		Node* mNode = nullptr;
	};
	
	List() = default;
	List(const std::initializer_list<T>& list) { 
		for (const T& t : list | boost::adaptors::reversed) 
			push_front(t); 
	}
	
	iterator begin() { return mBegin.get(); }
	const_iterator begin() const { return mBegin.get(); }
	iterator end() { return nullptr; }
	const_iterator end() const { return nullptr; }
	
	bool empty() const { return mSize == 0; }
	std::size_t size() const { return mSize; }
	
	T& front() { return mBegin->mData; }
	const T& front() const { return mBegin->mData; }
	
	void push_front(const T& data)
	{
		mBegin = std::make_unique<Node>(data, mBegin);
		mSize++;
	}
	void push_front(T&& data)
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
