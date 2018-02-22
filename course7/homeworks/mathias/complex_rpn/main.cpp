#include "rpn_calculator.h"
#include "complex.h"

#include <iostream>
#include <string>

int main(int , char** )
{
	RpnCalculator calc(std::cout);
	std::string line;

	while (std::getline(std::cin, line))
	{
		try
		{
			calc.parse(line);
		}
		catch (const std::runtime_error& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	return 0;
}
