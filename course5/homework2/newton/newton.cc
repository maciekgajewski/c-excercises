#include <iostream>
#include <string>

// Newton method of sqrt. The stack frame was 48 for Debug mode and 64 for Release mode.

float newton_sqrt( float y, int it, float x, int i, bool** start_address, bool** end_address)
{
    if( i == 0)
    {
        bool a;
        *start_address = &a;
    }
    else if( i == it )
    {
        bool a;
        *end_address = &a;
    }
    
    if( i < it )
    {
        i++;
        x -= ( x * x - y )/(2 * x);
        x = newton_sqrt( y, it, x, i, start_address, end_address );
    }
    
    return x;

}

int main(int argc, char** argv)
{
    const float y = std::stof(argv[1]); // input number
    float x = std::stof(argv[2]); //initial guess
    const int it = 1000;

    int i = 0;

    bool* start = nullptr;
    bool* end = nullptr;
    bool** start_address = &start;
    bool** end_address = &end;

    std::cout << "sqrt of " << argv[1] << " is " << newton_sqrt(y, it, x, i, start_address, end_address) << std::endl;

    std::cout << "depth" << "=" << it + 1 << std::endl;
    int size = (*start_address - *end_address)/it;
    std::cout << "size of stack frame" << "=" << (*start_address - *end_address)/it << std::endl;
    if (size > 0)
    {
        std::cout << "stack grows downwards" << std::endl;
    }
    else if (size < 0)
    {
        std::cout << "stack grows upwards" << std::endl;
    }

}