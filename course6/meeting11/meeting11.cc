#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>

using namespace std::literals;

bool IsWaldoOrCarmen(const std::string& search, const std::string& a, const std::string& b)
{
	return search == a || search == b;
}

struct IsAOrB
{
	bool operator()(const std::string& search) const
	{
		return search == a || search == b;
	}

	const std::string& a, b;
};


int main(int argc, char** argv)
{
	if (argc < 3)
		throw std::runtime_error("Usage: meeting11 SEARCH1 SEARCH2 [args ...]");

	std::string s1 = argv[1];
	std::string s2 = argv[2];
	const std::vector<std::string> args(argv+3, argv+argc);

	IsAOrB functor{s1, s2};

	functor("Waldo");

	auto it = std::find_if(args.begin(), args.end(), functor);

	if (it == args.end())
	{
		std::cout << "There is no Waldo!" << std::endl;
	}
	else
	{
		std::cout << "Waldo found!" << std::endl;
	}


}
 