#include "line_sorter.h"

namespace jds {

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

int ToNumeric(std::string const & value)
{
	try { return std::stoi(value); }
	catch (std::invalid_argument &) { return std::numeric_limits<int>::max(); }
	catch (std::out_of_range &) { return std::numeric_limits<int>::max(); }
}

void LineSorter::ReadLines(std::istream & source)
{
	std::string line;
	while (source)
	{
		std::getline(source, line);
		if (bool(source) || line.length())
			mLines.push_back(std::move(line));
	}
}

}
