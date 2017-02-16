#include <iostream>
#include <cmath>
#include <cstring>

float fast_inv_sqrt(float number)
{
    const float threehalfs = 1.5f;
    std::int32_t i;
    static_assert(sizeof(i) == sizeof(number), "Only 32bit float type supported");
    std::memcpy(&i, &number, sizeof(i));
    i = 0x5f3759df - (i >> 1);
    float y;
    std::memcpy(&y, &i, sizeof(i));
    float x2 = number*0.5f;
    y = y * (threehalfs - (x2*y*y));     // 1st iteration
    // y = y * (threehalfs - (x2*y*y));  // 2nd iteration, this can be removed
    return y;
}

int main()
{
    std::cout << "# x\tstd_inv_sqrt\tfast_inv_sqrt\tdifference\trelative error";
    for (int i=1; i<10000; ++i)
    {
        float x = (i/10.0f)*(i/10.0f);
        float reference = std::sqrt(x);
        float fast = 1.0f/fast_inv_sqrt(x);
        float diff = fast-reference;
        std::cout << x << "\t" << reference << "\t" << fast << "\t" << diff << "\t" << diff/x << std::endl;
    }
}
