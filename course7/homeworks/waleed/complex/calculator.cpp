#include "calculator.h"

#include <sstream>

void Calculator::PushLine(const std::string& str)
{
    if (str.size() == 1) // Operator
    {
        if (st.size() < 2)
        {
            throw std::runtime_error("Not enough operands to perform operation");
        }
        Complex operand2 = st.top(); st.pop();
        Complex operand1 = st.top(); st.pop();
        Complex newTop;
        switch (str[0])
        {
        case('+') :
            newTop = operand1 + operand2;
            break;
        case('*') :
            newTop = operand1 * operand2;
            break;
        case('-') :
            newTop = operand1 - operand2;
            break;
        case('/') :
            newTop = operand1 / operand2;
            break;
        }
        st.push(newTop);
    }
    else // Operand
    {
        std::stringstream ss(str);
        double r, i;
        char tmp;
        ss >> r >> tmp >> tmp >> i;
        Complex newTop(r, i);
        st.push(newTop);
    }
}

Complex Calculator::GetTop() const
{
    if (st.size() == 0)
    {
       throw std::runtime_error("Empty stack");
    }
    return st.top();
}

