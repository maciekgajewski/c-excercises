#include "complex.h"

Complex::Complex(double real, double imaginary) : mReal(real), mImaginary(imaginary)
{

}

Complex::Complex(const std::string& input)
{
    int index = 0;
    mReal = std::stod( input, &index);
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