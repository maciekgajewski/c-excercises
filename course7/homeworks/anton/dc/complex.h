#pragma once

#include <iostream>

namespace complex {

struct Complex
{
    Complex()
    {

    }

    Complex(double r, double i)
    {
        mR = r;
        mI = i;
    }

    Complex operator+(const Complex& rhs)
    {
        return Complex(mR + rhs.mR, mI + rhs.mI);
    }

    Complex operator-(const Complex& rhs)
    {
        return Complex(mR - rhs.mR, mI - rhs.mI);
    }

    Complex operator*(const Complex& rhs)
    {
        return Complex(mR*rhs.mR - mI*rhs.mI, mR*mI + rhs.mR*rhs.mI);
    }

    Complex operator/(const Complex& rhs)
    {
        double denomenator = rhs.mI*rhs.mR + rhs.mI*rhs.mI;
        return Complex((mR*rhs.mR - mI*rhs.mI)/denomenator, (mI*rhs.mR - mR*rhs.mI)/denomenator);
    }

    bool is_real()
    {
        return mI == 0.0;
    }

    double mR = 0.0;
    double mI = 0.0;
};

typedef Complex (*operation)(Complex&, Complex&);

Complex add(Complex& n1, Complex& n2);

Complex substruct(Complex& n1, Complex& n2);

Complex multiply(Complex& n1, Complex& n2);

Complex divide(Complex& n1, Complex& n2);
}

std::ostream& operator<<(std::ostream& s, const complex::Complex& rhs);

std::istream& operator>>(std::istream& s, complex::Complex& rhs);
