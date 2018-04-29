#pragma once

#include <iostream>

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

    Complex operator+(const Complex& rhs) const
    {
        return Complex(mR + rhs.mR, mI + rhs.mI);
    }

    Complex operator-(const Complex& rhs) const
    {
        return Complex(mR - rhs.mR, mI - rhs.mI);
    }

    Complex operator*(const Complex& rhs) const
    {
        return Complex(mR*rhs.mR - mI*rhs.mI, mR*mI + rhs.mR*rhs.mI);
    }

    Complex operator/(const Complex& rhs) const
    {
        double denomenator = rhs.mR*rhs.mR + rhs.mI*rhs.mI;
        return Complex((mR*rhs.mR - mI*rhs.mI)/denomenator, (mI*rhs.mR - mR*rhs.mI)/denomenator);
    }

    bool operator==(const Complex& rhs) const
    {
        return mR == rhs.mR && mI == rhs.mI;
    }

    bool is_real() const
    {
        return mI == 0.0;
    }

    double mR = 0.0;
    double mI = 0.0;
};

std::ostream& operator<<(std::ostream& s, const Complex& rhs);

std::istream& operator>>(std::istream& s, Complex& rhs);
