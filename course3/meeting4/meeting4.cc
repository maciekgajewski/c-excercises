#include <iostream>

void fun(int* arr)
{
    3[arr] = 333333;
    std::cout << "sizeof(arr)=" << sizeof(arr) << std::endl;
}

int main()
{
    int a[6] = { 1, 7, 11, 12, 99, 66};
    
    fun(a);
    //a[234] = 6;
    std::cout << "[";
    for(int i : a)
    {
        std::cout << i << ", ";
    }
    std::cout << "]" << std::endl;
    std::cout << "sizeof(a)=" << sizeof(a) << std::endl;
    
    std::cout << ("Hello!!"+1) << std::endl;
    
}