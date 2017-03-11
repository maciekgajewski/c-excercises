#include "vector2d.h"

#include <cmath>
#include <sstream>
#include <cassert>
#include <iostream>

#define EPS 0.0000001

void test_operators()
{
	Vector2d a = Vector2d::fromCarthesian(5, 6);
	Vector2d b = Vector2d::fromCarthesian(-1, 7);

	assert(a+b == Vector2d::fromCarthesian(4, 13));
	assert(a-b == Vector2d::fromCarthesian(6, -1));

	std::stringstream s;
	s << a;
	assert(s.str() == "(5, 6)");
}

void test_cart_get_set()
{
	Vector2d a = Vector2d::fromCarthesian(5, 6);

    assert(a.X() == 5);
    assert(a.Y() == 6);

    a.X(1);
    a.Y(-2);
    
    assert(a.X() == 1);
    assert(a.Y() == -2);
}

void test_polar_get_set()
{
    Vector2d a = Vector2d::fromPolar(1, M_PI/2);

    assert(a.Rho() == 1);
    assert(a.Phi() == M_PI/2);

    assert(std::abs(a.X()) < EPS);
    assert(std::abs(a.Y() - 1) <  EPS);

    a.Y(2);
    assert(std::abs(a.Rho()-2) < EPS);
    assert(std::abs(a.Phi()-M_PI/2) < EPS);
}

int main()
{
	// to make sture the code is compiled in debug mode
#ifdef NDEBUG
#error Compile the code in debug mode!
#endif

	std::cout << "Starting test..." << std::endl;	

    test_operators();
    test_cart_get_set();
    test_polar_get_set();

	std::cout << "done" << std::endl;
}
