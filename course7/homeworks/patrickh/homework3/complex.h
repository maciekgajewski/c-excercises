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

    double getReal() const;
    double getImaginary() const;
private:
    double mReal;
    double mImaginary;
};

std::ostream& operator<<(std::ostream& stream, const Complex& complex);