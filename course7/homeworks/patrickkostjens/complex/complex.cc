#include "complex.hh"

#include <cmath>
#include <iostream>

std::ostream& operator<< (std::ostream& stream, const Complex& complex)
{
	stream << complex.real << (complex.imaginary >= 0 ? "+" : "-") << "i" << std::abs(complex.imaginary);
	return stream;
}


