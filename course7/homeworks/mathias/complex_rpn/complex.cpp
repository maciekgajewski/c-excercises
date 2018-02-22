#include "complex.h"

#include <cmath>

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

std::ostream& operator<<(std::ostream& stream, const Complex& c)
{
	stream << c.real() << "+i" << c.imaginary();
	return stream;
}
