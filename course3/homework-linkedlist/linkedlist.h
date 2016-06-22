#pragma once
#include <iostream>
#include <memory>

namespace mau {

// Reverse iterator. http://stackoverflow.com/questions/8542591/c11-reverse-range-based-for-loop
template <typename T>
struct reversion_wrapper { T& iterable; };

template <typename T>
auto begin (reversion_wrapper<T> w) { return rbegin(w.iterable); }

template <typename T>
auto end (reversion_wrapper<T> w) { return rend(w.iterable); }

template <typename T>
reversion_wrapper<T> reverse (T&& iterable) { return { iterable }; }

template<typename T>
class list {
public:
    typedef ptrdiff_t difference_type;
    typedef std::forward_iterator_tag iterator_category;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;

    class Node {
    public:
        Node(const T& val, std::unique_ptr<Node>& next) : mData(val), mNext(std::move(next)) {}
        T mData;
        std::unique_ptr<Node> mNext;
    };

    class iterator {
    public:

        iterator(Node* node) : mNode(node) {}
        bool operator==(const iterator& it) { return mNode == it.mNode; }
        bool operator!=(const iterator& it) { return mNode != it.mNode; }
        iterator& operator++() { 
            mNode = mNode->mNext.get();
            return *this;
        }
        T& operator*() {
            return mNode->mData;
        }

        Node* mNode = nullptr;

    };

    class const_iterator {
    public:
        const_iterator(const iterator& it) : mNode(it.mNode) {}
        const_iterator(Node* node) : mNode(node) {}
        bool operator==(const const_iterator& it) { return mNode == it.mNode; }
        bool operator!=(const const_iterator& it) { return mNode != it.mNode; }
        const_iterator& operator++() { 
            mNode = mNode->mNext.get();
            return *this;
        }
        const T& operator*() {
            return mNode->mData;
        }

        Node* mNode = nullptr;
    };

    list() : mSize() {}

    list(const std::initializer_list<T> init) : mSize(0) {
        for(const auto i : reverse(init))
            push_front(i);

    }

    iterator begin() { return mHead.get(); }
    const iterator begin() const { return mHead.get(); }
    iterator end() { return nullptr; }
    const iterator end() const { return nullptr; }

    std::size_t size() const {
        return mSize;
    }

    bool empty() const {
        return mSize == 0;
    }

    void push_front(const T& value) {
        mHead = std::make_unique<Node>(value, mHead);
        mSize++;
    }

    void pop_front() {
        mHead = std::move(mHead->mNext);
        mSize--;
    }

    T& front() {
        return mHead->mData;
    }

    const T& front() const {
        return mHead->mData;
    }

    void erase(iterator it) {
        iterator e = begin();

        if (e == it) {
            pop_front();
            return;
        }

        while(e.mNode->mNext.get() != it.mNode)
            ++e;

        e.mNode->mNext = std::move(it.mNode->mNext);
        mSize--;
    }

private:
    std::size_t mSize;
    std::unique_ptr<Node> mHead = nullptr;

};
}
