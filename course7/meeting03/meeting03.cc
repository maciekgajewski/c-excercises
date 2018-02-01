#include <iostream>
#include <string>

struct Complex
{
	Complex() { std::cout << "Complex this=" << this << " default-created" << std::endl; }
	~Complex() { std::cout << "Complex this=" << this << " destroyed" << std::endl; }
	void print();

	double i = 0.0;
	double r = 0.0;
};

struct PairOfComplex
{
	Complex first;
	Complex second;
};

int main(int argc, char** argv)
{
	Complex c;
	
	PairOfComplex pc;
	c.i = 5;
	c.r = 88;

	auto ptr = &c;
	ptr->r = 3;

	std::cout << "Size of Complex is: " << sizeof(Complex) << std::endl;
	c.print();
}

void Complex::print()
{
	std::cout << r << " + i" << i << std::endl;
}

