#include "functions.hh"

#include <string>
#include <stdexcept>

static double str2dbl(const char* s)
{
	char* str_end = const_cast<char*>(s);
	double r = std::strtod(s, &str_end);
	if (str_end == s)
	{
		throw std::invalid_argument("Failed to convert string to double");
	}
	return r;
}


std::vector<double> paramsToNumbers(int argc, const char** argv)
{
	std::vector<double> out;
	out.reserve(argc);
	for(int i = 0; i < argc; i++)
	{
		out.push_back(str2dbl(argv[i]));
	}
	return out;
}