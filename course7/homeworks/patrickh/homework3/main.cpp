#include "calculator.h"
#include "iostream"

int main(int argc, char *argv[])
{
    Calculator calculator;
    std::string line;
    while(std::getline(std::cin, line))
    {
        try
        {
            calculator.parse(line);
        }
        catch(const std::runtime_error& error)
        {
            std::cout << "Some error occured: " << error.what() << std::endl;
        }
        calculator.printValue();
    }
}