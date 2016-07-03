#include "functions.hh"

#include <string>
#include <stdexcept>
#include <algorithm>
#include <iterator>

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
	std::transform(argv, argv+argc, std::back_inserter(out), [](const char* s) { return str2dbl(s); });
	return out;
}