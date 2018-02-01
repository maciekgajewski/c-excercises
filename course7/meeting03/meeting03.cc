#include <iostream>
#include <string>

struct Complex
{
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

	// Option, user defined
	Complex(double i, double r) 
	{
		std::cout << "Complex this=" << this << " created from r,i" << std::endl;
		this->i = i; this->r = r;
	}

	void print();

	double i = 0.0;
	double r = 0.0;
};

struct PairOfComplex
{
	Complex first;
	Complex second;
};

Complex make_complex(double r)
{
	return Complex(r, 0.0);
}

int main(int argc, char** argv)
{
	Complex a(3.3, 4.4);
	Complex b = a;
	Complex c(b);
	Complex d = make_complex(7);

	c = a; // assignment
	d = make_complex(88);

	a.print();
	b.print();
	c.print();
	d.print();
}

void Complex::print()
{
	std::cout << r << " + i" << i << std::endl;
}

