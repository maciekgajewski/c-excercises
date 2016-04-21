#include <iostream>
#include <array>

void fun(std::array<int, 5>& arr)
{
    arr[3] = 333333;
    std::cout << "sizeof(arr)=" << sizeof(arr) << std::endl;
}

int main()
{
    std::array<int, 6> a = { 1, 7, 11, 12, 99, 66};
    
    fun(a);
    
    //a.at(88) = 6;
    
    std::cout << "[";
    for(int i : a)
    {
        std::cout << i << ", ";
    }
    std::cout << "]" << std::endl;
    std::cout << "sizeof(a)=" << sizeof(a) << std::endl;
}