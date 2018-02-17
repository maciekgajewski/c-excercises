#include <iostream>
#include "complex.h"

Complex::Complex(double real, double imaginary) : mReal(real), mImaginary(imaginary)
{

}

Complex::Complex(const std::string& input)
{
    size_t index = 0;
    mReal = std::stod(input, &index);
    if(input.substr(index, 2 ) == "+i")
        mImaginary = std::stod(input.substr(index + 2));
}

Complex Complex::operator+(const Complex& other)
{
    return Complex(this->mReal + other.mReal, this->mImaginary + other.mImaginary);
}

Complex Complex::operator-(const Complex& other)
{
    return Complex(this->mReal - other.mReal, this->mImaginary - other.mImaginary);
}

Complex Complex::operator*(const Complex& other)
{
    return Complex(this->mReal * other.mReal - this->mImaginary * other.mImaginary, this->mImaginary * other.mReal + this->mReal * other.mImaginary);
}

Complex Complex::operator/(const Complex& other)
{
    double divisor = this->mReal * this->mReal + other.mImaginary * other.mImaginary;
    return Complex(
            (this->mReal * other.mReal + this->mImaginary * other.mImaginary) / divisor,
            (this->mImaginary * other.mReal - this->mReal * other.mImaginary) / divisor
    );
}

double Complex::getReal() const
{
    return this->mReal;
};

double Complex::getImaginary() const
{
    return this->mImaginary;
};

std::ostream& operator<<(std::ostream& stream, const Complex& complex)
{
    stream << complex.getReal() << "+i" << complex.getImaginary();
    return stream;
}