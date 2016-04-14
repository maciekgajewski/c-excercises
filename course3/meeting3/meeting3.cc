#include <iostream>

int& hey()
{
    int x = 5;
    x++;
    std::cout << "x=" << x << std::endl;
    //int* p = x;
    
    return x;
}

int main()
{
    std::cout << "Hello, world!" << std::endl;
    int& r = hey();
    std::cout << "r=" << r << std::endl;
}