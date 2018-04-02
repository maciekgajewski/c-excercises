#pragma once

#include "complex.h"
#include <memory>


class MyComplexLinkedList {
private:
    struct Node {
        Node(Complex payload, std::unique_ptr<Node> next) : mPayload(payload), mNext(std::move(next)) { }

        Complex mPayload;
        std::unique_ptr<Node> mNext;
    };

    std::unique_ptr<Node> mHead;
    std::size_t mSize = 0;

public:
    typedef Complex value_type;
    typedef Complex& reference;
    typedef const Complex& const_reference;
    typedef std::size_t size_type;

    class iterator {
        const Node* mCurr;
    public:
        iterator(const Node* node) : mCurr(node) {
        }

        iterator& operator++() {
            mCurr = mCurr->mNext.get();
            return *this;
        }

        const Complex& operator*() const {
            return mCurr->mPayload;
        }

        bool operator==(const iterator& rhs) const {
            return mCurr == rhs.mCurr;
        }

        bool operator!=(const iterator& rhs) const {
            return mCurr != rhs.mCurr;
        }
    };

    const iterator begin() {
        return iterator(mHead.get());
    }

    const iterator end() {
        return iterator(nullptr);
    }

    void push_back(const_reference item) {
        mHead = std::make_unique<Node>(item, std::move(mHead));
        ++mSize;
    }

    void pop_back() {
        if (!mHead)
            throw std::range_error("Stack is empty");
        mHead = std::move(mHead->mNext);
        --mSize;
    }

    reference back() {
        if (!mHead)
            throw std::range_error("Stack is empty");
        return mHead->mPayload;
    }

    const_reference back() const {
        if (!mHead)
            throw std::range_error("Stack is empty");
        return mHead->mPayload;
    }

    bool empty() const {
        return !mHead;
    }

    size_type size() const {
        return mSize;
    }
};
