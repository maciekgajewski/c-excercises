#include <stdexcept>
#include <limits>

#include "line_sorting.h"

namespace jds {

std::vector<std::string> ReadLines(std::istream & source)
{
	std::vector<std::string> lines;
	std::string line;
	while (source)
	{
		std::getline(source, line);
		if (bool(source) || line.length())
			lines.push_back(std::move(line));
	}
	return lines;
}

std::string FindColValue(std::string const & line, char separator, size_t column)
{
	size_t pos = 0;
	size_t currentCol = 1;
	while (currentCol < column)
	{
		size_t found = line.find(separator, pos);
		if (found == std::string::npos)
			return std::string();
		pos = found + 1;
		currentCol++;
	}
	size_t nextColPos = line.find(separator, pos);
	if (nextColPos == std::string::npos)
		return line.substr(pos, std::string::npos);
	else
		return line.substr(pos, nextColPos - pos);
}

long long ToNumeric(std::string const & value)
{
	try { return std::stoll(value); }
	catch (std::invalid_argument &) { return std::numeric_limits<long long>::max(); }
	catch (std::out_of_range &) { std::cerr << "Warning: numerical value out of range" << std::endl; return std::numeric_limits<long long>::max(); }
}

}
