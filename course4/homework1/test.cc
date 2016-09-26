#include "vector2d.h"

#include <sstream>
#include <cassert>
#include <iostream>

void print(const Vector2d& value)
{
	std::cout << value.GetRadius() << " " << value.GetAngle() << std::endl;
}

int main()
{
	std::cout << "Starting test..." << std::endl;	

	Vector2d a = {5, 6};
	Vector2d b = {-1, 7};

	assert((a+b == Vector2d{4, 13}));

	std::stringstream s;
	s << a;

	assert(s.str() == "(5, 6)");

	print(Vector2d{1, 0});
	print(Vector2d{0, 1});
	print(Vector2d{-1, 0});
	print(Vector2d{0, -1});
	print(Vector2d{1, 2});
	print(Vector2d{-1, 2});
	print(Vector2d{1, -2});
	print(Vector2d{-1, -2});
	std::cout << "done" << std::endl;
}