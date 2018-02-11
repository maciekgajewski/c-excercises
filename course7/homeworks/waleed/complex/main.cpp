#include "complex.h"
#include "calculator.h"

#include <string>
#include <iostream>
#include <fstream>

int main()
{
    std::string inp;
    Calculator calc;
    while (std::getline(std::cin, inp))
    {
        calc.PushLine(inp);
    }

    try
    {
        std::cout << calc.GetTop() << std::endl;
    }
    catch (std::exception)
    {
        std::cout << "Empty" << std::endl;
    }

    return 0;
}
