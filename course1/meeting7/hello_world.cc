#include <iostream>
#include "mat.h"
#include "log.h"

int main(int argc, char** argv)
{
    Calculator calc;
    Logger l;
    if (argc < 3)
        std::cerr << "Error: usage PROG a b" << std::endl;
    else
    {
        double a = std::stod(argv[1]);
        double b = std::stod(argv[2]);
        l.log("Calculating sum...");
        std::cout << "sum is " << calc.sum(a, b) << std::endl;
    }
}

