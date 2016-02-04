#include <iostream>
#include <memory>

template<typename T>
struct Node
{
	T mValue;
	std::unique_ptr<Node> mNext;
};

template<typename T>
class ListIterator
{
public:
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
class LinkedList
{
public:

	void push_front(const T& v)
	{
		std::unique_ptr<Node<T>> newNode(new Node<T>{v});
		newNode->mNext = std::move(mFront);
		mFront = std::move(newNode);
	}

	ListIterator<T> begin()
	{
		return ListIterator<T>(mFront.get());
	}

	ListIterator<T> end()
	{
		return ListIterator<T>(nullptr);
	}

private:

	std::unique_ptr<Node<T>> mFront;
};

int main()
{
	std::cout << "hw" << std::endl;

	LinkedList<int> l;
	for(int i = 0; i < 10; i++)
	{
		l.push_front(i);
	}

        for(auto it = l.begin(); it != l.end(); ++it)
        {
            int i = *it;
	//for(int i : l)
	//{
		std::cout << i << std::endl;
	}
}