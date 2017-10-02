#pragma once

#include <iostream>


template<typename T>
struct Vec2
{
    T x;
    T y;

    void print()
    {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
};


