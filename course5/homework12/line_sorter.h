#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

namespace jds {

std::string FindColValue(std::string const & line, char separator, size_t column);

int ToNumeric(std::string const & value);

class LineSorter
{
private:
	void ReadLines(std::istream & input);
public:
	using iterator = std::vector<std::string>::iterator;
	using const_iterator = std::vector<std::string>::const_iterator;

	LineSorter(std::istream & input, char separator = ',', size_t column = 1,
			bool reverse = false, bool numeric = false)
	{
		ReadLines(input);
		std::sort(mLines.begin(), mLines.end(), [&](std::string const & left, std::string const & right)
			  {
			  	bool result;
				auto leftValue = FindColValue(left, separator, column);
				auto rightValue = FindColValue(right, separator, column);
				if (numeric)
					result = ToNumeric(leftValue) < ToNumeric(rightValue);
				else
					result = leftValue < rightValue;
				return result != reverse;
			  });
	}
	iterator begin() { return mLines.begin(); }
	const_iterator begin() const { return mLines.begin(); }
	iterator end() { return mLines.end(); }
	const_iterator end() const { return mLines.end(); }
private:
	std::vector<std::string> mLines;
};

}
