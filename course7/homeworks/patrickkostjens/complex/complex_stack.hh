#pragma once

#include "complex.hh"

#include <memory>

struct ComplexStackNode
{
    ComplexStackNode(Complex value) : value(value) {}
    ComplexStackNode(const ComplexStackNode& original) : value(original.value)
    {
        if (original.next)
            this->next = std::make_unique<ComplexStackNode>(*original.next);
    }

    Complex value;
    std::unique_ptr<ComplexStackNode> next;
};

class ComplexStack
{
public:
    ComplexStack() = default;
    ComplexStack(const ComplexStack& original)
    {
        if (original.head)
            this->head = std::make_unique<ComplexStackNode>(*original.head);
    }

    Complex pop();
    Complex top() const;
    void push(Complex c);
    bool empty() const;

private:
    std::unique_ptr<ComplexStackNode> head;
};
