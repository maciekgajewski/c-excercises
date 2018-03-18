#pragma once
#include "complex.h"
#include "memory"
struct ComplexLinkedListNode
{

    ComplexLinkedListNode(Complex complex) : value(complex)
    {

    }
    ComplexLinkedListNode(const ComplexLinkedListNode& other) : value(other.value)
    {
        if (other.next)
            this->next = std::make_unique<ComplexLinkedListNode>(*other.next);
    }

    Complex value;
    std::unique_ptr<ComplexLinkedListNode> next;
};