#include <iostream>
#include <string>
#include <cmath>


float Carmack_sqrt(float number)
{
    const float threehalfs = 1.5F;
    float x2 = number * 0.5F;
    std::int32_t i  = *reinterpret_cast<int *>(&number);
    static_assert(sizeof(i)==sizeof(number), "error: not the same size");
    i  = 0x5f3759df - ( i >> 1 );
    float y  = *reinterpret_cast<float *>(&i);
    y  = y * ( threehalfs - ( x2 * y * y ) );

    return y;
}

int main(int argc, char** argv)
{
    for (int i= 1; i< argc; ++i) {
        auto input = std::stof(argv[i]);
        auto carmack_sqrt = 1.0 / Carmack_sqrt(input);
        auto std_sqrt = std::sqrt(input);
        auto diff = (carmack_sqrt - std_sqrt) / std_sqrt *100;
        std::cout << "carmack_sqrt " << carmack_sqrt << " is " << diff << "% different from std_sqrt " << std_sqrt << std::endl;
    }
}
