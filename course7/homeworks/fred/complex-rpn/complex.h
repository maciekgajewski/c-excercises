#pragma once

struct Complex
{
  double real;
  double imaginary;

  Complex operator+ (const Complex& other) const;
  Complex operator- (const Complex& other) const;
  Complex operator* (const Complex& other) const;
  Complex operator/ (const Complex& other) const;
};

template <typename Stream>
Stream& operator<< (Stream& stream, const Complex& c) {
  stream << c.real;
  if (c.imaginary >= 0.0)
    stream << '+';
  stream << c.imaginary << 'i';
  return stream;
}
