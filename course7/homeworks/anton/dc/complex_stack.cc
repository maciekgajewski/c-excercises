#include "complex_stack.h"

bool digit_is_comming(std::istream& s)
{
    return '0' <= s.peek() && s.peek() <= '9';
}

bool number_is_comming(std::istream& s)
{
    return '_' == s.peek() || 'i' == s.peek() || digit_is_comming(s);
}

std::ostream& ComplexStack::operator>>(std::ostream& s)
{
    std::stack<complex::Complex> tmp_stack;
    while(!stack.empty()) {
        std::cout << stack.top() << std::endl;
        tmp_stack.push(stack.top());
        stack.pop();
    }

    while(!tmp_stack.empty()) {
        stack.push(tmp_stack.top());
        tmp_stack.pop();
    }
    return s;
}

bool ComplexStack::try_read_number(std::istream& s)
{
    if (number_is_comming(std::cin))
    {
        complex::Complex number;
        std::cin >> number;
        stack.push(number);
        return true;
    }
    return false;
}

void ComplexStack::exec_operation(complex::operation op)
{
    if (stack.size() < 2)
        std::cerr << "stack is empty" << std::endl;
    else
    {
        auto& arg2 = stack.top();
        stack.pop();
        auto& arg1 = stack.top();
        stack.pop();
        stack.push(op(arg1, arg2));
    }
}

std::ostream& operator<<(std::ostream& s, ComplexStack& rhs)
{
    rhs >> s;
    return s;
}
