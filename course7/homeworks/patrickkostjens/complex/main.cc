#include "calculator.hh"

#include <string>

int main(int argc, char** argv)
{
	Calculator c;
	std::string line;
	while(true)
	{
		std::getline(std::cin, line);
		try
		{
			c.process_line(line);
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
		c.print_status(std::cout);
	}
}