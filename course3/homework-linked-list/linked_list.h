#pragma once

#include <memory>


template<class T>
class LinkedList
{
public:

    LinkedList(): head(nullptr), tail(nullptr), length(0) { }

    const T* begin() const {
        return this->head ? this->head->data : nullptr;
    }

    T* begin() {
        return this->head ? this->head->data : nullptr;
    }

    const T* end() const {
        return this->tail ? this->tail->data : nullptr;
    }

    T* end() {
        return this->tail ? this->tail->data : nullptr;
    }

    std::size_t size() const {
        return this->length;
    }

    bool empty() const {
        return this->length == 0;
    }

    void push_front(const T& input) {
        auto n = Node(input);
        n.next = this->head;
        this->head = &n;
        this->length++;
    }

    void pop_front() {
        if (this->empty()) {
            throw std::out_of_range("The list is empty");
        }
        auto topop = this->head;
        this->head = this->head->next;
        delete topop;
        this->length--;
    }

    const T& front() const {
        return *this->head;
    }

    T& front() {
        return *this->head;
    }

private:
    class Node {
    public:
        T* data;
        Node* next;

        Node(T data) {
            this->data = new int(data);
        }
    };

    Node* head;
    Node* tail;
    std::size_t length;
};
