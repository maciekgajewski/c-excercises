#include <iostream>

struct Vector
{
	int x;
	int y;
};

int main(int /*argc*/, char** /*argv*/)
{
	Vector v = {4, 6};
	Vector& r = v;
	r.x = 8;
	
	std::cout << "Vector = {" << v.x << ", " << v.y << ")" << std::endl;
}

