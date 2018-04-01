#pragma once

#include "complex.h"
#include <memory>


class Stack {
private:
    struct Node {
        Node(Complex payload, std::unique_ptr<Node> next) : mPayload(payload), mNext(std::move(next)) { }

        Complex mPayload;
        std::unique_ptr<Node> mNext;
    };

    std::unique_ptr<Node> mHead;
    std::size_t mSize = 0;

public:
    void push(const Complex& item) {
        mHead = std::make_unique<Node>(item, std::move(mHead));
        ++mSize;
    }

    void pop() {
        if (!mHead)
            throw std::range_error("Stack is empty");
        mHead = std::move(mHead->mNext);
        --mSize;
    }

    Complex& top() {
        if (!mHead)
            throw std::range_error("Stack is empty");
        return mHead->mPayload;
    }

    bool empty() { return !mHead; }

    std::size_t size() { return mSize; }
};
