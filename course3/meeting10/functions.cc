#include "functions.hh"

#include <string>

std::vector<double> paramsToNumbers(int argc, const char** argv)
{
	std::vector<double> out;
	for(int i = 0; i < argc; i++)
	{
		out.push_back(std::stod(argv[i]));
	}
	return out;
}