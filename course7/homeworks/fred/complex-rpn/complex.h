#pragma once

#include <ostream>

struct Complex
{
  Complex(double real, double imaginary)
    : real(real)
    , imaginary(imaginary) {}

  explicit Complex()
    : Complex(0.0, 0.0) {}

  explicit Complex(const std::string&);

  double real;
  double imaginary;

  Complex operator+ (const Complex& other) const;
  Complex operator- (const Complex& other) const;
  Complex operator* (const Complex& other) const;
  Complex operator/ (const Complex& other) const;
};

std::ostream& operator<< (std::ostream& stream, const Complex& c);
