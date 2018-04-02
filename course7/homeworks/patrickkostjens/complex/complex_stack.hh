#pragma once

#include "complex.hh"

#include <memory>


class ComplexStack
{
public:
    ComplexStack() = default;
    ComplexStack(const ComplexStack& original)
    {
        if (original.head)
            this->head = std::make_unique<ComplexStackNode>(*original.head);
    }

    void pop_back();
    Complex& back() const;
    void push_back(Complex c);

    bool empty() const
    {
        return !head;
    };
    size_t size() const
    {
        return element_count;
    }

    using value_type = Complex;
    using size_type = size_t;
    using reference = Complex&;
    using const_reference = const Complex&;

private:
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

    std::unique_ptr<ComplexStackNode> head;
    size_t element_count;
};
