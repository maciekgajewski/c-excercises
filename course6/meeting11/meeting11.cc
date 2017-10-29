#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <functional>

using namespace std::literals;

bool IsWaldoOrCarmen(const std::string& search, const std::string& a, const std::string& b)
{
	return search == a || search == b;
}

struct IsAOrB
{
	template<typename ArgumentType>
	int operator()(const ArgumentType& search)
	{
		return search == a || search == b;
	}

	const std::string& a, b;
};

using namespace std::placeholders;

int main(int argc, char** argv)
{
	if (argc < 3)
		throw std::runtime_error("Usage: meeting11 SEARCH1 SEARCH2 [args ...]");

	std::string s1 = argv[1];
	std::string s2 = argv[2];
	const std::vector<std::string> args(argv+3, argv+argc);

	auto it = std::find_if(args.begin(), args.end(), 
		[&] (const std::string& s) { return s == s1 || s == s2; }
	);

	if (it == args.end())
	{
		std::cout << "There is no Waldo!" << std::endl;
	}
	else
	{
		std::cout << "Waldo found!" << std::endl;
	}


}
 