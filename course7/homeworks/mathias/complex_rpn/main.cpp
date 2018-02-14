#include "rpn_calculator.h"
#include "complex.h"

#include <iostream>
#include <string>

int main(int , char** )
{
	RpnCalculator calc;
	std::string line;

	std::cout << "> ";
	while (std::getline(std::cin, line))
	{
		try
		{
			calc.parse(line);
		}
		catch (const std::runtime_error& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}

		if (calc.hasTopValue())
			std::cout << "= " << calc.topValue() << std::endl;

		std::cout << "> ";
	}
	return 0;
}
