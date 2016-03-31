#include <iostream>
#include <cstdint>

int main(int argc, char** argv)
{
    int64_t x = 7;
    double d = 5;
    const char* text = "Hello, world!";

    int64_t* px = &x;
    double* pd = &d;
    
    std::cout << px << std::endl;
    std::cout << pd << std::endl;
    
    auto y = "f";
    
    px = reinterpret_cast<int64_t*>(pd);
    
    std::cout << *px << std::endl;
    
} 
