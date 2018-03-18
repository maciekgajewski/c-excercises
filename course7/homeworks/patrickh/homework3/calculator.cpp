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
        mStack.push(input);
}

void Calculator::add()
{
    if(mStack.size() < 2)
        throw new std::runtime_error("Not enough elements on the stack");
    Complex c1 = mStack.top();
    mStack.pop();
    Complex c2 = mStack.top();
    mStack.pop();
    mStack.push(c1 + c2);
}

void Calculator::subtract()
{
    if(mStack.size() < 2)
        throw new std::runtime_error("Not enough elements on the stack");
    Complex c1 = mStack.top();
    mStack.pop();
    Complex c2 = mStack.top();
    mStack.pop();
    mStack.push(c1 - c2);
}

void Calculator::multiply()
{
    if(mStack.size() < 2)
        throw new std::runtime_error("Not enough elements on the stack");
    Complex c1 = mStack.top();
    mStack.pop();
    Complex c2 = mStack.top();
    mStack.pop();
    mStack.push(c1 * c2);
}

void Calculator::divide()
{
    if(mStack.size() < 2)
        throw new std::runtime_error("Not enough elements on the stack");
    Complex c1 = mStack.top();
    mStack.pop();
    Complex c2 = mStack.top();
    mStack.pop();
    mStack.push(c1 / c2);
}

void Calculator::printValue()
{
    if(!mStack.empty())
    {
        std::cout << "=" << mStack.top() << std::endl;
    }
    else
    {
        std::cout << "Empty" << std::endl;
    }
}