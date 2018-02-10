#include <iostream>
#include <string>
#include <sstream>

class Complex
{
public:

	using component = double;

	// The big 6
	Complex() { std::cout << "Complex this=" << this << " default-created" << std::endl; }
	~Complex() { std::cout << "Complex this=" << this << " destroyed" << std::endl; }
	Complex(const Complex& src) {
		std::cout << "Complex this=" << this << " constructed as a copy of " << &src << std::endl;
		r = src.r; i = src.i;
	}
	Complex(Complex&& src) {
		std::cout << "Complex this=" << this << " move-constructed from " << &src << std::endl;
		r = src.r; i = src.i;
	}

	Complex& operator =(const Complex& src)
	{
		std::cout << "Complex this=" << this << " copy-assigned " << &src << std::endl;
		r = src.r; i = src.i;
		return *this;
	}

	Complex& operator =(Complex&& src)
	{
		std::cout << "Complex this=" << this << " move-assigned " << &src << std::endl;
		r = src.r; i = src.i;
		return *this;
	}

	// Optional, user defined
	Complex(double r, double i) 
	{
		std::cout << "Complex this=" << this << " created from r,i" << std::endl;
		this->i = i; this->r = r;
	}

	Complex(double r) 
	{
		std::cout << "Complex this=" << this << " created from r" << std::endl;
		this->i = 0; this->r = r;
	}
	void print();

	Complex operator+(const Complex& rhs) const
	{
		return Complex(r+rhs.r, i+rhs.i);
	}

	Complex operator+(double r) const
	{
		return Complex(r+this->r, this->i);
	}

	double get_r() const { return r; }
	double get_i() const { return i; }

	static double len(const Complex& c) { return c.r + c.i; }

private:
	component i = 0.0;
	component r = 0.0;
};


Complex operator+(double r, const Complex& rhs)
{
	return Complex(r+rhs.get_r(), rhs.get_i());
}


bool operator ==(Complex lhs, Complex rhs)
{
	return lhs.get_i()==rhs.get_i() && lhs.get_r()==rhs.get_r();
}

std::ostream& operator<<(std::ostream& s, const Complex& c)
{
	s << c.get_r() << "+i" << c.get_i();
	return s;
}

Complex operator "" _i(long double d)
{
	return Complex(0.0, d);
}

struct PairOfComplex
{
	Complex first;
	Complex second;
};

void fun(const Complex& c)
{
	std::cout << "fun(" << c << ")" << std::endl;
}

int main(int argc, char** argv)
{
	Complex c = 2.2 + 6.6_i;
	Complex a = 7.7;
	Complex d = {1.1, 4.4};
	Complex b(7.7);
	std::cout << c << std::endl;
	fun(Complex(1.234));

	Complex::component x = 5.5;

	std::cout << "l=" << Complex::len(c) << std::endl;
}

void Complex::print()
{
	std::cout << r << " + i" << i << std::endl;
}

