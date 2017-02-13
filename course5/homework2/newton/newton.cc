#include <iostream>
#include <string>

// Newton method of sqrt. The stack frame was 48 for Debug mode and 64 for Release mode.

bool* start = nullptr;
bool* end = nullptr;

float function( float y, int it, float& rx, int& ri)
{
    if( ri == 0)
    {
        bool a;
        start = &a;
    }
    else if( ri == it )
    {
        bool a;
        end = &a;
    }

    while( ri < it)
    {
        ri++;
        rx -= ( rx * rx - y )/(2 * rx);
        function( y, it, rx, ri );
    }

    return rx;

}

int main(int argc, char** argv)
{
    const float y = std::stof(argv[1]); // input number
    float x = std::stof(argv[2]); //initial guess
    const int it = 1000;

    int i = 0;

    int& ri = i;
    float& rx = x;

    std::cout << "sqrt of " << argv[1] << " is " << function(y, it, rx, ri) << std::endl;

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

}