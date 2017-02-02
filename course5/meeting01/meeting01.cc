#include <iostream>

double global = 6.6;

int main(int argc, char** argv)
{
	int x = 7;
	float y = 5.6;
	x = y;
	std::cout << "x=" << x << std::endl;
	
	int* xp = &x;
	float* yp = &y;
	
	std::cout << "xp=" << xp << std::endl;
	std::cout << "yp=" << yp << std::endl;
	std::cout << "&global=" << &global << std::endl;
}

