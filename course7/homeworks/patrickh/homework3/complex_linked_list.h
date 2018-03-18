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
    void clear();
    Complex back();

    bool empty()
    {
        return nr_elements == 0;
    }

private:
    std::unique_ptr<ComplexLinkedListNode> head;
    size_t nr_elements;
};