#include <iostream>
#include <stdio.h>

int i = 0;
float x;

float function( float y, int it )
{
    while( i < it)
    {
        i++;
        x -= ( x * x - y )/(2 * x);
        std::cout << x << std::endl;
        std::cout << i << std::endl;
        function(y, it);
    }

    return x;

}

int main(int argc, char** argv)
{
    const float y = std::atof(argv[1]);
    x = std::atof(argv[2]);
    const int it = std::atoi(argv[3]);

    std::cout << function(y, it) << std::endl;
}