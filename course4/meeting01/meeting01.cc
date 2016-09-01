#include <iostream>

int c = 10;

int fac(int x)
{
	std::cout << "x=" << x << ", addr=" << &x << std::endl;
	if (x <= 1)
		return 1;
	else
		return x * fac(x-1);
}

int main(int argc, char** argv)
{
	auto f = fac(3);
	std::cout << "3! = " << f << std::endl;
}

