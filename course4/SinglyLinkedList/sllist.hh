#pragma once
#include <memory>
#include <iostream>

namespace course {

template<class T>
struct Node
{
    T mData;
    std::unique_ptr<Node> mNext;
};

template<class T>
class iterator: public std::iterator<std::forward_iterator_tag, T>
{
private:
    Node<T>* p;
public:
    iterator(Node<T>* p) : p(p) {}
    iterator& operator=(iterator other)
    {
        std::swap(p, other.p);
        return *this;
    }
    const T& operator*() const { return p->mData; }
    bool operator==(const iterator& other) { return p == other.p; }
    bool operator!=(const iterator& other)
    {
        //std::cout<<p<<" != "<<other.p<<std::endl;
        return p != other.p;
    }

    void operator++() { p = p->mNext.get();}
};

template<class T>
class sllist
{
 public:
    sllist()
    {
        mBegin = nullptr;
        mSize = 0;
    }

    iterator<T> begin()
    {
        return iterator<T>(mBegin.get());
    }

    iterator<T> end()
    {
        auto temp = mBegin.get();
        while(temp->mNext != nullptr)
        {
            temp = temp->mNext.get();
        }

        return iterator<T>(temp);
    }

    const iterator<T> begin() const
    {
        return begin();
    }

     const iterator<T> end() const
     {
        return end();
     }

    bool empty() const
    {
        if(mBegin==nullptr)
            return true;

        return false;
    }

    int size()
    {
        return mSize;
    }

    T front()
    {
        return mBegin->mData;
    }

    void push_front(const T& value)
    {
        std::unique_ptr<Node<T>> newNodePtr(new Node<T>);
        newNodePtr->mData = value;
        newNodePtr->mNext = std::move(mBegin);
        mBegin = std::move(newNodePtr);
        mSize++;
    }

    T pop_front()
    {
        auto temp = std::move(mBegin);
        mBegin = std::move(temp->mNext);
        mSize--;
        return temp->mData;

    }
 private:
    std::unique_ptr<Node<T>> mBegin;
    int mSize;
};
}
