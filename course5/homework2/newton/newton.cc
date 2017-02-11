#include <iostream>
#include <string>
#include <time.h>

// Newton method of sqrt. The stack frame was 48 for Debug mode and 64 for Release mode.

int i = 0;
float x;
bool* start = nullptr;
bool* end = nullptr;

float function( float y, int it)
{
    if( i == 0)
    {
        bool a;
        start = &a;
    }
    else if( i == it )
    {
        bool a;
        end = &a;
    }

    while( i < it)
    {
        i++;
        x -= ( x * x - y )/(2 * x);
        function( y, it);
    }

    return x;

}

int main(int argc, char** argv)
{
    const float y = std::stof(argv[1]); // input number
    x = std::stof(argv[2]); //initial guess
    const int it = std::stoi(argv[3]); // number of iterations

    clock_t t = clock();
    std::cout << "sqrt of " << argv[1] << " is " << function(y, it) << std::endl;
    t = clock() - t;

    std::cout << "depth" << "=" << i + 1 << std::endl;
    int size = (start - end)/i;
    std::cout << "size of stack frame" << "=" << (start - end)/i << std::endl;
    if (size > 0)
    {
        std::cout << "stack grows downwards" << std::endl;
    }
    else if (size < 0)
    {
        std::cout << "stack grows upwards" << std::endl;
    }

    std::cout << "calculation time: " << t << std::endl;
}