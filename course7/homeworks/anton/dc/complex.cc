#include "complex.h"
#include <cmath>
#include <iostream>

bool digit_is_comming(std::istream& s);

std::ostream& operator<<(std::ostream& s, const complex::Complex& rhs)
{
    if (rhs.mR == 0.0)
    {
        if (rhs.mI > 0.0)
            s << "i" << std::fabs(rhs.mI);
        else if (rhs.mI < 0.0)
            s << "-i" << std::fabs(rhs.mI);
        else
            s << rhs.mR;
    }
    else
    {
        s << rhs.mR;
        if (rhs.mI > 0.0)
            s << "+i" << std::fabs(rhs.mI);
        else if (rhs.mI < 0.0)
            s << "-i" << std::fabs(rhs.mI);
     }

    return s;
}

std::istream& operator>>(std::istream& s, complex::Complex& rhs)
{
    bool isPositive = true;
    bool isImaginary = false;
    double modulus = 0.0;

    if ('_' == s.peek())
    {
        s.ignore(1);
        isPositive = false;
    }

    if ('i' == s.peek())
    {
        s.ignore(1);
        isImaginary = true;
        modulus = 1.0;
    }

    if (digit_is_comming(s))
        s >> modulus;

    if (isImaginary)
        rhs.mI = isPositive ? modulus : -modulus;
    else
        rhs.mR = isPositive ? modulus : -modulus;

    return s;
}

namespace complex {
Complex add(Complex& n1, Complex& n2)
{
    return n1 + n2;
}

Complex substruct(Complex& n1, Complex& n2)
{
    return n1 - n2;
}

Complex multiply(Complex& n1, Complex& n2)
{
    return n1 * n2;
}

Complex divide(Complex& n1, Complex& n2)
{
    return n1 / n2;
}
}
