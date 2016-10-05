#include "vector2d.h"

#include <sstream>
#include <cassert>
#include <iostream>
#include <cmath>
int main()
{
	// to make sture the code is compiled in debug mode
#ifdef NDEBUG
#error Compile the code in debug mode!
#endif

	std::cout << "Starting test..." << std::endl;	

	Vector2d a = {5, 6};
    Vector2d b{0,0};
    b.SetX(-1);
    b.SetY(7);

	assert((a+b == Vector2d{4, 13}));

	std::stringstream s;
	s << a;

	assert(s.str() == "(5, 6)");

    const double rho = 1.0;
    const double phi = M_PI / 4;
    auto polar = Vector2d::createByPolarCoordinates(rho, phi);
    std::stringstream ss;
    ss << polar;
    std::cout << ss.str() << std::endl;

    assert(polar.GetRho() == rho);
    assert(polar.GetPhi() == phi);
	std::cout << "done" << std::endl;
}
