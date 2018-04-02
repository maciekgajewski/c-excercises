#pragma once

#include "complex.hh"
#include <memory>

class Complex;

class ComplexLinkedList
{
public:
	typedef Complex value_type;
	typedef Complex& reference;
	typedef const Complex& const_reference;
	typedef std::size_t size_type;

	bool empty() const;
	std::size_t size() const;

	Complex& back();
	const Complex& back() const;

	void push_back(const Complex& value);
	void pop_back();

private:
	struct Node
	{
		Complex mData;
		std::unique_ptr<ComplexLinkedList::Node> mNext;

		Node(const Complex& data, std::unique_ptr<ComplexLinkedList::Node>&& next) : mData(data), mNext(std::move(next)) {}
	};

	std::unique_ptr<Node> mTopNode = nullptr;
	int mSize = 0;
};
