#include "complex_linked_list.hh"

bool ComplexLinkedList::empty() const
{
	return mSize == 0;
}

std::size_t ComplexLinkedList::size() const
{
	return mSize;
}

Complex& ComplexLinkedList::back()
{
	return mTopNode->mData;
}

const Complex& ComplexLinkedList::back() const
{
	return mTopNode->mData;
}

void ComplexLinkedList::push_back(const Complex& value)
{
	mTopNode = std::make_unique<ComplexLinkedList::Node>(value, std::move(mTopNode));
	++mSize;
}

void ComplexLinkedList::pop_back()
{
	mTopNode = std::move(mTopNode->mNext);
	--mSize;
}
