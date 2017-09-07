#include <iostream>
#include <iomanip>

struct Vector
{
	int x;
	int y;

	void print() const
	{
		std::cout << "const (" << x << ", " << y << ")" << std::endl;
	}

	void print()
	{
		std::cout << "non const (" << x << ", " << y << ")" << std::endl;
	}

};

int main(int argc, char** argv)
{
	const Vector v{44, 55};

	v.print();

	Vector x = v;
	x.print();
}

