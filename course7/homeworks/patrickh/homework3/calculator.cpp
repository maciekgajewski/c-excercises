#include <stdexcept>
#include <iostream>
#include "calculator.h"

void Calculator::parse(const std::string& input)
{
    if (input == "+")
        add();
    else if (input == "-")
        subtract();
    else if (input == "*")
        multiply();
    else if (input == "/")
        divide();
    else
        mStack.emplace(input);
}

void Calculator::add()
{
    if(mStack.size() < 2)
        throw std::runtime_error("Not enough values to be added");
    Complex c1 = mStack.top();
    mStack.pop();
    Complex c2 = mStack.top();
    mStack.pop();
    mStack.emplace(c1 + c2);
}

void Calculator::subtract()
{
    if(mStack.size() < 2)
        throw std::runtime_error("Not enough values to be subtracted");
    Complex c1 = mStack.top();
    mStack.pop();
    Complex c2 = mStack.top();
    mStack.pop();
    mStack.emplace(c1 - c2);
}

void Calculator::multiply()
{
    if(mStack.size() < 2)
        throw std::runtime_error("Not enough values to be multiplied");
    Complex c1 = mStack.top();
    mStack.pop();
    Complex c2 = mStack.top();
    mStack.pop();
    mStack.emplace(c1 * c2);
}

void Calculator::divide()
{
    if(mStack.size() < 2)
        throw std::runtime_error("Not enough values to be divided");
    Complex c1 = mStack.top();
    mStack.pop();
    Complex c2 = mStack.top();
    mStack.pop();
    mStack.emplace(c1 / c2);
}

void Calculator::printValue()
{
    if(mStack.size() > 0)
    {
        std::cout << "=" << mStack.top() << std::endl;
    }
    else
    {
        std::cout << "Empty" << std::endl;
    }
}