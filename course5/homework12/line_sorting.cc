#include <stdexcept>
#include <limits>
#include <boost/tokenizer.hpp>

#include "line_sorting.h"

namespace jds {

std::vector<std::string> ReadLines(std::istream & source)
{
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(source, line))
	{
		if (bool(source) || line.length())
			lines.push_back(std::move(line));
	}
	return lines;
}

std::string FindColValue(std::string const & line, char const * separators, size_t column)
{
	boost::tokenizer<boost::char_separator<char>> tokenizer{line, boost::char_separator<char>{separators}};
	auto current = tokenizer.begin();
	for (size_t currentCol = 1; currentCol < column && current != tokenizer.end(); ++currentCol)
	{
		++current;
	}
	if (current == tokenizer.end())
		return std::string();
	return *current;
}

long long ToNumeric(std::string const & value)
{
	try { return std::stoll(value); }
	catch (std::invalid_argument &) { return std::numeric_limits<long long>::max(); }
	catch (std::out_of_range &) { std::cerr << "Warning: numerical value out of range" << std::endl; return std::numeric_limits<long long>::max(); }
}

}
