#pragma once

#include <memory>


template<class T>
class LinkedList
{
public:

    LinkedList();

    const T* begin() const;
    T* begin();
    const T* end() const;
    T* end();

    std::size_t size() const;
    bool empty() const;

    void push_front(const T&);
    void pop_front();

    const T& front() const;
    T& front();

private:
    class Node {
    public:
        T data;
        Node* next;

        Node(T input);
    };

    Node* head;
    Node* tail;
    std::size_t length;
};
