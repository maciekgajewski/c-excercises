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
	int len;
	int& count;
	bool operator() (const std::string& s) { count++; return s.length() == len; }
};

int main(int argc, char** argv)
{
	std::vector<std::string> strings(argv, argv+argc);
	
	int counter = 0;
	IsWaldo pred{7, counter};
	auto it = std::find_if(strings.begin(), strings.end(), pred);

	if (it == strings.end())
		std::cout << "No Waldo :(" << std::endl;
	else
		std::cout << "Waldo found at pos " << it - strings.begin() << std::endl;
	
	std::cout << "The predicate has been invoked " << counter << " times" << std::endl;
}
