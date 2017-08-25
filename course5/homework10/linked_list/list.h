#pragma once

#include <memory>
#include <ostream>

#include <iostream>

namespace List {

template <typename T>
class List
{
public:
	List() = default;
	~List() = default;

	List(const List& copy) { *this = copy; }

	List(List&& move) { *this = std::move(move); }

	List& operator=(const List& copy)
	{
		mSize = copy.mSize;
		mFirstNode.reset();

		std::shared_ptr<Node> ptr;
		std::shared_ptr<Node> previousPtr;

		for (auto& node : copy)
		{
			ptr = std::make_shared<Node>(node);
			if (previousPtr)
				previousPtr->mNextNode = ptr;
			else
				mFirstNode = ptr;
			previousPtr = ptr;
		}
		return *this;
	}

	List& operator=(List&& move)
	{
		mFirstNode = std::move(move.mFirstNode);
		mSize = move.mSize;
	}

	void push_front(const T& copy)
	{
		mFirstNode = std::make_shared<Node>(mFirstNode, copy);
		++mSize;
	}

	void push_front(T&& move)
	{
		mFirstNode = std::make_shared<Node>(mFirstNode, std::move(move));
		++mSize;
	}

	template<typename... Args>
	void emplace_front(Args&&... args)
	{
		mFirstNode = std::make_shared<Node>(mFirstNode, args...);
		++mSize;
	}

	void pop_front()
	{
		// TODO what to do if there are no more nodes left?
		//
		mFirstNode = mFirstNode->mNextNode;
		--mSize;
	}

	// TODO what should we return if mSize == 0?
	T& front() { return mFirstNode->mObj; }
	const T& front() const { return mFirstNode->mObj; }
	size_t size() const { return mSize; }


//private:
	struct Node
	{
		Node() = default;

		Node(const T& copy): mObj(copy) { }

		template<typename... Args>
		Node(std::shared_ptr<Node> next, Args&&... args):
			mObj(args...),
			mNextNode(next) { std::cout << "Arg constructed node" << std::endl; }

		Node(std::shared_ptr<Node> next, const T& copy):
			mObj(copy),
			mNextNode(next) { std::cout << "Copy constructed node" << std::endl; }

		Node(std::shared_ptr<Node> next, T&& move):
			mObj(move),
			mNextNode(next) { std::cout << "Move constructed node" << std::endl; }

		T mObj;
		std::shared_ptr<Node> mNextNode;
	};

	size_t mSize = 0;
	std::shared_ptr<Node> mFirstNode;

public:
	class ListIterator:
		public std::iterator<std::input_iterator_tag, T, int, T*, T&>
	{
	public:
		explicit ListIterator(Node* ptr): mPtr(ptr) { }
		ListIterator operator++() { mPtr = mPtr->mNextNode.get(); return *this; }
		bool operator==(ListIterator rhs) const { return mPtr == rhs.mPtr; }
		bool operator!=(ListIterator rhs) const { return !(*this == rhs); }
		T& operator*() { return mPtr->mObj; }

	private:
		Node* mPtr;
	};

	using Iterator = ListIterator;
	using Const_iterator = ListIterator;

	Iterator begin() { return Iterator(mFirstNode.get()); }
	Iterator end() { return Iterator(nullptr); }

	Const_iterator begin() const { return Const_iterator(mFirstNode.get()); }
	Const_iterator end() const { return Const_iterator(nullptr); }
};

}
