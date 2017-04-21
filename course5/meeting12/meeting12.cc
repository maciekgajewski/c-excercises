#include <boost/range/algorithm.hpp>

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>

using namespace std::literals;

int main(int argc, char** argv)
{
	std::vector<std::string> args(argv, argv+argc);
	
	auto it = boost::find(args, "Waldo");
	
	std::cout << ((it == args.end()) ? "Not found"s : "Found"s) << std::endl;
}
