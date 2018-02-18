#pragma once

#include "complex.h"
#include "stack"


class ComplexStack
{
public:
    std::ostream& operator>>(std::ostream& s);

    bool try_read_number(std::istream& s);

    void exec_operation(complex::operation op);

    void add()
    {
        exec_operation(complex::add);
    }

    void substruct()
    {
        exec_operation(complex::substruct);
    }

    void multiply()
    {
        exec_operation(complex::multiply);
    }

    void divide()
    {
        exec_operation(complex::divide);
    }

    complex::Complex& top()
    {
        return stack.top();
    }

    void clear()
    {
        stack = std::stack<complex::Complex>();
    }

private:
    std::stack<complex::Complex> stack;
};

std::ostream& operator<<(std::ostream& s, ComplexStack& rhs);
