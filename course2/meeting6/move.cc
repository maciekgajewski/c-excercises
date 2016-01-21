#include "string.hh"


int main()
{
    MyString a = "a";
    MyString b = "b";
    MyString ab = a+b;
    std::cout << ab << std::endl;
    ab = b+a;
    std::cout << ab << std::endl;
    ab = std::move(a);
    std::cout << ab << std::endl;
}