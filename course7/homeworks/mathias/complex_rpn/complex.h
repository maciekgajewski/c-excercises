#pragma once

#include <iostream>
#include <string>

class Complex
{
public:
	Complex(double real, double imaginary);
	explicit Complex(const std::string& str);

	Complex operator+(const Complex& rhs) const
	{
		return Complex{ mReal + rhs.mReal, mImaginary + rhs.mImaginary };
	}

	Complex operator-(const Complex& rhs) const
	{
		return Complex{ mReal - rhs.mReal, mImaginary - rhs.mImaginary };
	}

	Complex operator*(const Complex& rhs) const
	{
		return Complex{ mReal * rhs.mReal - mImaginary * rhs.mImaginary, mImaginary * rhs.mReal + mReal * rhs.mImaginary };
	}

	Complex operator/(const Complex& rhs) const
	{
		double divisor = std::pow(rhs.mReal, 2) + std::pow(rhs.mImaginary, 2);
		return Complex{
			(mReal * rhs.mReal + mImaginary * rhs.mImaginary) / divisor,
			(mImaginary * rhs.mReal - mReal * rhs.mImaginary) / divisor
		};
	}

	double real() const { return mReal; }
	double imaginary() const { return mImaginary; }

private:
	double mReal = 0.0;
	double mImaginary = 0.0;
};

std::ostream& operator<<(std::ostream& stream, const Complex& c);