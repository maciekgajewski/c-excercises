#include "vector.h"

#include <cassert>

int main()
{
    using namespace Course;
    auto vec = 3.3_x + 0.7_y;
    assert(vec == Vector2D(3.3, 0.7));
    std::cout << Vector2D(5, 10) - Vector2D(0, 5) << std::endl;
    std::cout << 10_x + 5_y << std::endl;
    std::cout << 10_r * 5_rad + 10_x << std::endl;
    std::cout << 3_y + 10_r * 5_deg << std::endl;
    std::cout << Vector2D::FromPolar(10, 90_deg) << std::endl;

    vec += Vector2D(3,5);
    std::cout << vec << std::endl;

    vec -= Vector2D(3,5);
    std::cout << vec << std::endl;

    auto vec2 = 10_r * 180_deg;
    std::cout << "R: " << vec2.GetR() << " deg: " << vec2.GetO() << std::endl;

    Vector2D a(3, 4);
    assert(-a == Vector2D(-3, -4));
}
