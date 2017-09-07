#include <iostream>
#include <iomanip>
#include <cmath>

struct Vector
{
	double x = 0.0;
	double y = 0.0;
};

int main(int argc, char** argv)
{
	int x = 7;
	int y = 8;
	int& ref = x;

	ref = y;

	y = 77;

	std::cout << "ref=" << ref << std::endl;	
	std::cout << "x=" << x << std::endl;
	std::cout << "y=" << y << std::endl;

	Vector& ref;
	{
		Vector v{44, 55};
		ref = v;
	}
	std::cout << ref.x << std::endl;

}

