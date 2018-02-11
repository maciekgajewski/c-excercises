#pragma once

#include <iostream>

class Complex
{
public:
    Complex() :
        mR(0.0),
        mI(0.0) {}
	Complex(double r, double i) :
        mR(r),
        mI(i) {}
    Complex operator+(const Complex& arg);
    Complex operator-(const Complex& arg);
    Complex operator/(const Complex& arg);
    Complex operator*(const Complex& arg);

    double GetR() const;

    double GetI() const;

private:
    double mR;
    double mI;
};

inline std::ostream& operator<<(std::ostream& os, const Complex& arg)
{
    os << arg.GetR() << " + i" << arg.GetI();
    return os;
}
