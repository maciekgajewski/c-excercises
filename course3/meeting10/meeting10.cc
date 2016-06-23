#include <iostream>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iterator>

int main(int argc, char** argv)
{
	using namespace std::literals;
	
	std::unordered_map<std::string, int> args = {
		{"One", 1},
		{"Two", 2},
	};
	
	std::transform(argv, argv+argc, std::inserter(args, args.end()),
		[&](char* in) { return std::make_pair(in, args.size()); });
	
	for(const auto& a : args)
		std::cout << a.first << " => " << a.second << std::endl;
	
	auto it = args.find("Wally");
	if (it == args.end())
		std::cout << "no wally" << std::endl;
	else
		std::cout << "Wally at pos " << it->second << std::endl;
	
	//args.insert(std::make_pair("maciek", 77));
	args.insert({"maciek"s, 77});
	int maciek = args["maciek"];
	std::cout << "maciek at pos " << maciek << std::endl;
	
	
	
}
