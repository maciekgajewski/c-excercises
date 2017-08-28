#include <iostream>
#include <cmath>
#include "vector2d.h"

int main(int, char**)
{
        jds::Vector2D cartesian(1, 0);
        jds::Vector2D polar = jds::Vector2D::Polar(1, 0);
        std::cout << "cartesian: x=" << cartesian.GetX() << ", y=" << cartesian.GetY() << ", r=" << cartesian.GetR() << ", phi=" << cartesian.GetPhi() << std::endl;
        std::cout << "polar: x=" << polar.GetX() << ", y=" << polar.GetY() << ", r=" << polar.GetR() << ", phi=" << polar.GetPhi() << std::endl;
        std::cout << "Polar(1, 0) == Vector2D(1, 0) = " << (polar == cartesian) << std::endl;
        std::cout << "cartesian + cartesian = " << cartesian + cartesian << std::endl;
        std::cout << "cartesian - cartesian = " << cartesian - cartesian << std::endl;
        std::cout << "-cartesian = " << -cartesian << std::endl;

        jds::Vector2D scratch(3, 4);
        std::cout << scratch << " -= " << cartesian << ": ";
        scratch -= cartesian;
        std::cout << scratch << std::endl;
        std::cout << scratch << " -= " << cartesian << ": ";
        scratch -= cartesian;
        std::cout << scratch << std::endl;
        std::cout << scratch << " += " << cartesian << ": ";
        scratch += cartesian;
        std::cout << scratch << std::endl;

        return 0;
}
