#pragma once
#include <iostream>
#include <memory>

namespace mau {
template<typename T>
class list {
public:
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
            mNode = mNode->mHead.get();
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
            mNode = mNode->mHead.get();
            return *this;
        }
        T& operator*() {
            return mNode->mData;
        }

        Node* mNode = nullptr;
    };

    list() : mSize() {}

    std::size_t size() {
        return mSize;
    }

    bool empty() {
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

private:
    std::size_t mSize;
    std::unique_ptr<Node> mHead = nullptr;

};
}
