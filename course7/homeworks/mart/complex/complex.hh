#pragma once

#include <iostream>

struct Complex
{
	Complex() = default;
	Complex(double r) : real(r) {}
	Complex(double r, double i) : real(r) , imaginary(i) {}
	Complex(const Complex& src) : real(src.real) , imaginary(src.imaginary) {}

	Complex& operator=(const Complex& src)
	{
		real = src.real;
		imaginary = src.imaginary;
		return *this;
	}

	Complex operator+(const Complex& rhs) const
	{
		return { real + rhs.real, imaginary + rhs.imaginary };
	}

	Complex operator-(const Complex& rhs) const
	{
		return { real - rhs.real, imaginary - rhs.imaginary };
	}

	Complex operator*(const Complex& rhs) const
	{
		return {
			(real * rhs.real) - (imaginary * rhs.imaginary),
			(real * rhs.imaginary) + (imaginary * rhs.real)
		  };
	}

	Complex operator/(const Complex& rhs) const
	{
		return {
			((real * rhs.real) + (imaginary * rhs.imaginary)) / ((rhs.real * rhs.real) + (rhs.imaginary * rhs.imaginary)),
			((imaginary * rhs.real) - (real * rhs.imaginary)) / ((rhs.real * rhs.real) + (rhs.imaginary * rhs.imaginary))
		  };
	}

	bool operator==(const Complex& rhs)
	{
		return real == rhs.real && imaginary == rhs.imaginary;
	}

	double real = 0.0;
	double imaginary = 0.0;
};

inline std::ostream& operator<<(std::ostream& stream, const Complex& complex)
{
	stream << complex.real << "+i" << complex.imaginary;
	return stream;
}
