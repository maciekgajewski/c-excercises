#include "vector2d.h"
#include<cassert>

int main()
{
    using namespace homework;
    Vector2D vector(-30, 90);
    std::cout << vector.GetTheta() << std::endl;

    auto vec1 = 3.3_x + 0.7_y; //copy constructor
    assert(vec1==Vector2D(3.3, 0.7));

    std::cout << Vector2D(6.5, 100) + Vector2D(100, 0) << std::endl;
    std::cout << Vector2D(6.5, 100) - Vector2D(0, 0) << std::endl;
    std::cout << -Vector2D(6.5, 100) << std::endl;

    auto vec2 = 6.5_x - 10.0_y; //copy constructor
    vec2 += Vector2D(5, 5);
    std::cout << vec2 << std::endl;
    vec2 -= Vector2D(5, 5);
    std::cout << vec2 << std::endl;

    std::cout << (Vector2D(6.5, 100) == Vector2D(5, 5)) << std::endl;
    std::cout << (Vector2D(6.5, 100) != Vector2D(5, 5)) << std::endl;

    Vector2D vec3 = (100.0_r + 1.5_theta); //copy constructor
    std::cout << vec3 << std::endl;

}
