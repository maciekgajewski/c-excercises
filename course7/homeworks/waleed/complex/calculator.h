#pragma once

#include "complex.h"

#include <stack>

class Calculator
{
public:
    void PushLine(const std::string& str);
    Complex GetTop() const;

private:
    std::stack<Complex> st;
};
