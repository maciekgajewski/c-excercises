#include "vector2d.h"

#include <sstream>
#include <cassert>
#include <iostream>

int main()
{
	// to make sure the code is compiled in debug mode
#ifdef NDEBUG
#error Compile the code in debug mode!
#endif

        std::cout << "Starting test..." << std::endl;

        Vector2d a = Vector2d::Rectangular(5, 6);
        Vector2d b = Vector2d::Polar(7.0710678118655, 98.130102354156); //{-1, 7};

        assert((a+b == Vector2d::Rectangular(4, 13)));

	std::stringstream s;
	s << a;

	assert(s.str() == "(5, 6)");

	std::cout << "done" << std::endl;
}
