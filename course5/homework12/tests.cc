#include <iostream>
#include <cassert>
#include <limits>

#include "line_sorting.h"

int main(int, char **)
{
	std::string line = "1,monkey,in a bag";
	std::string col1Value = jds::FindColValue(line, ',', 1);
	assert(col1Value == "1");
	std::string col2Value = jds::FindColValue(line, ',', 2);
	assert(col2Value == "monkey");
	std::string col3Value = jds::FindColValue(line, ',', 3);
	assert(col3Value == "in a bag");
	std::string col4Value = jds::FindColValue(line, ',', 4);
	assert(col4Value == "");

	assert(jds::ToNumeric("1") == 1);
	assert(jds::ToNumeric("-1") == -1);
	assert(jds::ToNumeric("   -2   ") == -2);
	assert(jds::ToNumeric("") == std::numeric_limits<int>::max());
	assert(jds::ToNumeric("one hundred") == std::numeric_limits<int>::max());
	assert(jds::ToNumeric("9000000000") == std::numeric_limits<int>::max());

	std::cout << "All tests passed" << std::endl;
	return 0;
}
