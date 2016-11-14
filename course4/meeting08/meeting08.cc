#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <string>
#include <cstring>

#include <boost/range/algorithm.hpp>

struct StringComparer
{
	const char* b;
	template<typename T>
	bool operator()(const char* a) const
	{
		return std::strcmp(a, b) == 0;
	}
};


int main(int argc, char** argv)
{
	auto cmp = [b=argv[1]](auto a) { return std::strcmp(a, b) == 0; };
	std::cout 
		<< std::count_if(argv+2, argv+argc, cmp)
		<< std::endl;
	
}
