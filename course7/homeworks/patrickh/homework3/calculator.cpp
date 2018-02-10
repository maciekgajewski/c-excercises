#include <stdexcept>
#include "calculator.h"

void Calculator::parse(const std::string& input)
{
    if (input == "+")
        return add();
    else if (input == "+")
        return add();
    else if (input == "*")
        return add();
    else if (input == "/")
        return add();
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