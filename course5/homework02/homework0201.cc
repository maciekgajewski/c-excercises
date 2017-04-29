#include <iostream>
#include <cmath>
#include <cfloat>

/****
homework02, part 1
Implement Carmack’s fast square root. Compare the values it produces with the output of std::sqrt for a range of values, draw conclusions.

Carmack’s fast square root, from Wikipedia:
an algorithm that estimates 1/sqrt(x), the reciprocal (or multiplicative inverse) of the square root of a 32-bit floating-point number x in IEEE 754 floating-point format.
The algorithm accepts a 32-bit floating-point number as the input and stores a halved value for later use. Then, treating the bits representing the floating-point number as a 32-bit integer, a logical shift right by one bit is performed and the result subtracted from the magic number 0x5f3759df. This is the first approximation of the inverse square root of the input. Treating the bits again as a floating-point number, it runs one iteration of Newton's method, yielding a more precise approximation.
***/

float carmack_sqrt(float input)
{
    int32_t* fl_to_int = reinterpret_cast<int32_t*>(&input);

    int32_t shifted_rt = *fl_to_int >> 1;
    int32_t from_magic = 0x5f3759df - shifted_rt;

    float* int_to_fl = reinterpret_cast<float*>(&from_magic);

    float result = 1 / *int_to_fl;
    result = result - (( result * result - input) / (2 * result));

    return result;
}

int main(int argc, char** argv)
{
    float inputs[23] = {
        FLT_MIN, 0.000234, 0.001, 0.087, 0.5,
        5, 13, 19, 52, 78, 9283657, FLT_MAX,
        0, 1, 4, 9, 16, 25, 36, 49, 400, 1024
    };

    for (auto input : inputs) {
        float carmack_result = carmack_sqrt(input);
        float stdlib_result = std::sqrt(input);
        float diff = carmack_result - stdlib_result;
        std::cout << std::endl << "Input -----------------> "  << input << std::endl;
        std::cout << "Carmack ---> " << carmack_result << std::endl;
        std::cout << "StdLib  ---> " << stdlib_result << std::endl;
        std::cout << "Diff          ------> " << diff << std::endl;
        std::cout << "Relative diff ------> " << diff / input << std::endl;
    }
}
