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
        mStack.push_back(input);
}

void Calculator::add()
{
    Complex c1 = mStack.back();
    mStack.pop_back();
    Complex c2 = mStack.back();
    mStack.pop_back();
    mStack.push_back(c1 + c2);
}

void Calculator::subtract()
{
    Complex c1 = mStack.back();
    mStack.pop_back();
    Complex c2 = mStack.back();
    mStack.pop_back();
    mStack.push_back(c1 - c2);
}

void Calculator::multiply()
{
    Complex c1 = mStack.back();
    mStack.pop_back();
    Complex c2 = mStack.back();
    mStack.pop_back();
    mStack.push_back(c1 * c2);
}

void Calculator::divide()
{
    Complex c1 = mStack.back();
    mStack.pop_back();
    Complex c2 = mStack.back();
    mStack.pop_back();
    mStack.push_back(c1 / c2);
}

void Calculator::printValue()
{
    if(!mStack.empty())
    {
        std::cout << "=" << mStack.back() << std::endl;
    }
    else
    {
        std::cout << "Empty" << std::endl;
    }
}