#include<string>
class Complex
{
public:
    Complex(double real, double imaginary);
    Complex(const std::string& input);
    Complex operator+(const Complex &other);
    Complex operator-(const Complex &other);
    Complex operator*(const Complex &other);
    Complex operator/(const Complex &rhs);

private:
    double mReal;
    double mImaginary;
};

