#pragma once

#include <vector>
#include <string>
#include <iostream>

namespace jds {

std::vector<std::string> ReadLines(std::istream & input);

std::string FindColValue(std::string const & line, char const * separator, size_t column);

long long ToNumeric(std::string const & value);

}
