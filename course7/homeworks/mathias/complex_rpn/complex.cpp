#include "complex.h"

Complex::Complex(double real, double imaginary)
	: mReal(real)
	, mImaginary(imaginary)
{ }

Complex::Complex(const std::string & str)
{
	size_t index = 0;

	try
	{
		mReal = std::stod(str, &index);

		if (str.substr(index, 2) == "+i")
		{
			mImaginary = std::stod(str.substr(index + 2));
		}
	}
	catch (const std::invalid_argument&)
	{
		throw std::runtime_error("Input could not be convert to a complex number.");
	}
	catch (const std::out_of_range&)
	{
		throw std::runtime_error("Input value too big to store.");
	}
}

Complex Complex::operator+(const Complex& rhs)
{
	return Complex { mReal + rhs.mReal, mImaginary + rhs.mImaginary };
}

Complex Complex::operator-(const Complex& rhs)
{
	return Complex { mReal - rhs.mReal, mImaginary - rhs.mImaginary };
}

Complex Complex::operator*(const Complex& rhs)
{
	return Complex { mReal * rhs.mReal - mImaginary * rhs.mImaginary, mImaginary * rhs.mReal + mReal * rhs.mImaginary };
}

Complex Complex::operator/(const Complex& rhs)
{
	double divisor = std::pow(rhs.mReal, 2) + std::pow(rhs.mImaginary, 2);
	return Complex {
		(mReal * rhs.mReal + mImaginary * rhs.mImaginary) / divisor,
		(mImaginary * rhs.mReal - mReal * rhs.mImaginary) / divisor
	};
}

std::ostream& operator<<(std::ostream& stream, const Complex& c)
{
	stream << c.real() << "+i" << c.imaginary();
	return stream;
}
