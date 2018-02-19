#include "complex.h"

Complex Complex::operator+(const Complex& arg)
{
    return Complex(mR + arg.mR, mI + arg.mI);
}

Complex Complex::operator-(const Complex& arg)
{
    return Complex(mR - arg.mR, mI - arg.mI);
}

Complex Complex::operator*(const Complex& arg)
{
    return Complex(mR * arg.mR - mI * arg.mI, mR * arg.mR + mI * arg.mI);
}

Complex Complex::operator/(const Complex& arg)
{
    return Complex(mR / arg.mR, 0.0);
}
