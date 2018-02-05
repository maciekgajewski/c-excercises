#include <iostream>
#include <string>

struct Complex
{
	Complex() = default;
	Complex(double r) : real(r) {}
	Complex(double r, double i) : real(r) , imaginary(i) {}
	~Complex() = default;
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

	double real = 0.0;
	double imaginary = 0.0;
};


bool operator==(Complex lhs, Complex rhs)
{
	return lhs.real == rhs.real && lhs.imaginary == rhs.imaginary;
}

std::ostream& operator<<(std::ostream& stream, const Complex& complex)
{
	stream << complex.real << "+i" << complex.imaginary;
	return stream;
}

int main(/*int argc, char** argv*/)
{
	Complex d = {1.1, 4.4};
	Complex b(7.7);
	std::cout << b << std::endl;
}
