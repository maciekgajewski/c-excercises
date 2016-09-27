#include "vector2d.h"

#include <sstream>
#include <cassert>
#include <iostream>

int main()
{
	// to make sture the code is compiled in debug mode
#ifdef NDEBUG
#error Compile the code in debug mode!
#endif

	std::cout << "Starting test..." << std::endl;	

	Vector2d a = {5, 6};
	Vector2d b = {-1, 7};

	assert((a+b == Vector2d{4, 13}));

	std::stringstream s;
	s << a;

	assert(s.str() == "(5, 6)");
	
	double pi = 3.14159265358979323846;
	std::cout << Vector2d(PolarCoords2d(5, pi/2)) << std::endl;

	std::cout << "done" << std::endl;
}
