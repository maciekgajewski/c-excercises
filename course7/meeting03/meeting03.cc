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

void fun1(int x)
{
	if (x > 2)
		throw std::runtime_error("Boo!");
}

void fun2(int x)
{
	Complex c;
	c.i = x;

	fun1(x);

	c.print();
}


int main(int argc, char** argv)
{
	try
	{
		fun2(argc);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void Complex::print()
{
	std::cout << r << " + i" << i << std::endl;
}

