#include <iostream>
#include <set>
#include <string>

int main(int argc, char** argv)
{
	std::set<std::string, std::greater<std::string>> args(argv, argv+argc);
	
	for(const auto& a : args)
		std::cout << a << " ";
	std::cout << std::endl;
	
	auto it = args.find("Elvis");
	if (it != args.end())
		std::cout << "Elvis is in the house!" << std::endl;
}

