#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

// functions:

bool is_waldo(const std::string& s) { return s == "Waldo"; }
bool is_waldo_no_case(const std::string& s) { return s == "Waldo" || s == "waldo"; }

// functors:

int main(int argc, char** argv)
{
	std::vector<std::string> strings(argv, argv+argc);
	
	int counter = 0;
	int len = 7;
	
	auto it = std::find_if(strings.begin(), strings.end(), 
					[&counter, len](const std::string& s)
					{
						counter++; return s.length() == len;
					});

	if (it == strings.end())
		std::cout << "No Waldo :(" << std::endl;
	else
		std::cout << "Waldo found at pos " << it - strings.begin() << std::endl;
	
	std::cout << "The predicate has been invoked " << counter << " times" << std::endl;
}
