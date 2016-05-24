#include <iostream>
#include <string>


int main(int argc, char** argv)
{
    std::string name;
    std::cout << "Whats your name? > ";
    std::cin >> name;
    std::cout << "Hello, " << name << std::endl;
    std::cout << "size of std::string is: " << sizeof(name) << std::endl;
    
} 
