#include <iostream>
#include <string>

class Complex
{
public:
	Complex(double real, double imaginary);
	explicit Complex(const std::string& str);

	Complex operator+(const Complex& rhs);
	Complex operator-(const Complex& rhs);
	Complex operator*(const Complex& rhs);
	Complex operator/(const Complex& rhs);

	double real() const { return mReal; }
	double imaginary() const { return mImaginary; }

private:
	double mReal = 0.0;
	double mImaginary = 0.0;
};

std::ostream& operator<<(std::ostream& stream, const Complex& c);
