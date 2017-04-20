#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

// functions:

bool is_waldo(const std::string& s) { return s == "Waldo"; }
bool is_waldo_no_case(const std::string& s) { return s == "Waldo" || s == "waldo"; }

// functors:

struct IsWaldo
{
	bool operator() (const std::string& s) { return s == "Waldo"; }
};

int main(int argc, char** argv)
{
	std::vector<std::string> strings(argv, argv+argc);
	
	auto it = std::find_if(strings.begin(), strings.end(), is_waldo);
	if (it == strings.end())
		std::cout << "No Waldo :(" << std::endl;
	else
		std::cout << "Waldo found at pos " << it - strings.begin() << std::endl;
	
	auto it2 = std::find_if(strings.begin(), strings.end(), is_waldo_no_case);
	if (it2 == strings.end())
		std::cout << "(case insensitive) No Waldo :(" << std::endl;
	else
		std::cout << "(case insensitive) Waldo found at pos " << it2 - strings.begin() << std::endl;
	
}
