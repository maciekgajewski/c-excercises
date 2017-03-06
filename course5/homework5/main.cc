#include "vector.h"
#include <iostream>
#include <cmath>

int main(int, char**)
{
    using namespace vector;

    auto v = 1.0_x + 2.2_y;

    std::cout << "v = "<< v << std::endl;

    auto  u = 2*0.785398_phi;

    std::cout << "u = " << u << std::endl;

    u.SetY(8.0);

    std::cout << "u = " << u << std::endl;

    u-= (1.0_x + 1.0_y);

    std::cout << "u = " << u << std::endl;

    v += u;

    std::cout << "v = " << v << std::endl;

    std::cout << "-v = " << -v << std::endl;

    std::cout << "v == u: " << (v == u) << std::endl;

    std::cout << "v != u: " << (v != u) << std::endl;

    std::cout << "magnitude of v: " << v.GetR() << std::endl;

    std::cout << "angle of v: " << v.GetAngle() << std::endl;
    
    Vector2D w = u;

    std::cout << "w = " << w << std::endl;

    w = v;

    std::cout << "w = " << w << std::endl;

    w.SetX(0.2);

    w.SetY(0.4);

    std::cout << "w = " << w << std::endl;

    std::cout << "w - u + v = " << w - u + v << std::endl;

}