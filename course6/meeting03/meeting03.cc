#include <iostream>
#include <cstdint>

class Vector
{
public:
	using coord = double;

	coord x = 0.0;
	coord y = 3.14;

	Vector operator + (Vector b) { return {x+b.x, y+b.y}; }
};

Vector operator - (Vector l, Vector r) { return { l.x - r.x, l.y - r.y}; }

std::ostream& operator<<(std::ostream& s, Vector v)
{
	return s << "Vector(" << x << ", " << y << ")";
}

int main(int argc, char** argv)
{
	Vector a{2, 3};
	Vector b{6, 7};

	std::cout << (a + b) << std::endl;
	std::cout << a - b << std::endl;
}

