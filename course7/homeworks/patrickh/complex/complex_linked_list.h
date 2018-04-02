#pragma once
#include "complex_linked_list_node.h"
#include "memory"


class ComplexLinkedList
{
public:
    ComplexLinkedList() = default;
    ComplexLinkedList(const ComplexLinkedList& other)
    {
        if (other.head)
            this->head = std::make_unique<ComplexLinkedListNode>(*other.head);
    }

    void pop_back();

    void push_back(const Complex& complex);

    Complex& back() const;

    size_t size() const
    {
        return nr_elements;
    }

    bool empty() const
    {
        return !head;
    }

    using value_type = Complex;
    using size_type = size_t;
    using reference = Complex&;
    using const_reference = const Complex&;
private:
    std::unique_ptr<ComplexLinkedListNode> head;
    size_t nr_elements = 0;
};