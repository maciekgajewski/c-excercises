#include <iostream>

struct Vector;

void print(const Vector& );

struct Carrier;

struct Plane
{
	Carrier* carrier;
};

struct Carrier
{
	std::vector<Plane> planes;
};


struct Vector
{
	int x;
	int y;
};


int main(int /*argc*/, char** /*argv*/)
{
	Vector v = {1, 55};
	
	print(v);
}

void print(const Vector& vec)
{
	std::cout << "(" << vec.x << ", " << vec.y << ")" << std::endl;
}
