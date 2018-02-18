#include "complex.h"

#include <stdexcept>

Complex::Complex(const std::string& s)
{
  std::string::size_type sz;

  try {
    this->real = std::stod(s, &sz);
  }
  catch (const std::logic_error& er) {
    throw std::runtime_error("Not a number number");
  }

  this->imaginary = 0.0;
  if (sz < s.size()) {
    if (s[sz] == '+') {
      ++sz;
    }
    else if (s[sz] != '-') {
      throw std::runtime_error("Invalid complex number");
    }

    auto secondPart = s.substr(sz);
    this->imaginary = std::stod(secondPart, &sz);

    if (sz != secondPart.size() - 1 || secondPart[sz] != 'i') {
      throw std::runtime_error("Invalid complex number");
    }
  }
}

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
  int denominator = (other.real * other.real) + (other.imaginary * other.imaginary);

  Complex result;
  result.real = ((this->real * other.real) + (this->imaginary * other.imaginary)) / denominator;
  result.imaginary = ((this->imaginary * other.real) - (this->real * other.imaginary)) / denominator;
  return result;
}

std::ostream& operator<< (std::ostream& stream, const Complex& c) {
  stream << c.real;

  if (c.imaginary >= 0.0)
    stream << '+';
  stream << c.imaginary << 'i';

  return stream;
}
