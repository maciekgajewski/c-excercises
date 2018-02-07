#include "complex.h"

#include <stdexcept>

Complex Complex::operator+ (const Complex& other) const
{
  Complex result;
  result.real = this->real + other.real;
  result.imaginary = this->imaginary + other.imaginary;
  return result;
}

Complex Complex::operator- (const Complex& other) const
{
  Complex result;
  result.real = this->real - other.real;
  result.imaginary = this->imaginary - other.imaginary;
  return result;
}

Complex Complex::operator* (const Complex& other) const
{
  Complex result;
  result.real = (this->real * other.real) - (this->imaginary * other.imaginary);
  result.imaginary = (this->imaginary * other.real) + (this->real * other.imaginary);
  return result;
}

Complex Complex::operator/ (const Complex& other) const
{
  if (other.real == 0.0 && other.imaginary == 0.0) {
    // TODO check with epsilon?
    throw std::runtime_error("Division by zero");
  }

  int denominator = (other.real * other.real) + (other.imaginary * other.imaginary);

  Complex result;
  result.real = ((this->real * other.real) + (this->imaginary * other.imaginary)) / denominator;
  result.imaginary = ((this->imaginary * other.real) - (this->real * other.imaginary)) / denominator;
  return result;
}
