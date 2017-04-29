#include <iostream>
#include <math.h>
#include <time.h>
#include <string>

// Implementing fast-sqrt algortihm. However, for me, sqrt from the math library seems much faster.

float inv_sqrt( float x )
{
    int i;
    float x2 = 0.5 * (x);
    float y = x;
    const int magic = 0x5f3759df;

    float* p = &y;
    int* p2 = reinterpret_cast<int*>(p);
    i = *p2;
    i = * reinterpret_cast<int*>(&y);
    i = magic - ( i >> 1);

    y = *reinterpret_cast<float*>(&i);
    y = y * ( 1.5 - ( x2 *y *y) );

    return y;
}

int main(int argc, char** argv)
{
    float x = std::stof(argv[1]);
    clock_t t;
    t = clock();
    std::cout << "Carmack_sqrt of " << argv[1] << "=" << 1/inv_sqrt(x) << std::endl;
    t = clock() - t;
    std::cout << "Carmack_time" << "=" << t << std::endl;
    t = clock();
    std::cout << "math_sqrt of"  << "=" << sqrt(x) << std::endl;
    t = clock() - t;
    std::cout << "math_time"  << "=" << t << std::endl;
}