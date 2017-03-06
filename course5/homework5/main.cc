#include "vector.h"
#include <iostream>

int main(int, char**)
{
    using namespace vector;

    auto v = 1.0_x + 2.2_y;

    std::cout << "v = "<< v << std::endl;
    
    auto  u = 2*45.0_phi;

    std::cout << "u = " << u << std::endl;

    u.SetY(8.0);

    std::cout << "u = " << u << std::endl;

    v += u;

    std::cout << "v = " << v << std::endl;

    std::cout << "v == u: " << (v == u) << std::endl;

    std::cout << "v != u: " << (v != u) << std::endl;
    
}