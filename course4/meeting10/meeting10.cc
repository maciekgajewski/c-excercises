#include <iostream>
#include <set>
#include <unordered_set>
#include <string>

int main(int argc, char** argv)
{
	std::unordered_set<std::string> args(argv, argv+argc);
	
	for(const auto& a : args)
		std::cout << a << " ";
	std::cout << std::endl;
	
	auto it = args.find("Elvis");
	if (it != args.end())
		std::cout << "Elvis is in the house!" << std::endl;
}

