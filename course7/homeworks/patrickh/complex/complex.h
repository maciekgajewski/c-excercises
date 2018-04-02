#pragma once
#include<string>
class Complex
{
public:
    Complex(double real, double imaginary);
    Complex(const std::string& input);
    Complex operator+(const Complex &other);
    Complex operator-(const Complex &other);
    Complex operator*(const Complex &other);
    Complex operator/(const Complex &rhs);

    bool operator== (const Complex& rhs) const
    {
        return mReal == rhs.mReal && mImaginary == rhs.mImaginary;
    }

    double getReal() const;
    double getImaginary() const;
private:
    double mReal;
    double mImaginary;
};

std::ostream& operator<<(std::ostream& stream, const Complex& complex);