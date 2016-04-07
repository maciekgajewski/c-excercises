#include <iostream>
#include <cstdint>

int main(int argc, char** argv)
{
    int64_t x = 7;
    int64_t y = 77;
    double d = 5;
    const char* text = "Hello, world!";

    int64_t* px = &x;
    double* pd = &d;
    
    int64_t& rx = *px;
    double& rd = d;
    
    std::cout << "x=" << x << std::endl;
    *px = 66;
    std::cout << "x=" << x << std::endl;
    rx = 123;
    std::cout << "x=" << x << std::endl;
} 
