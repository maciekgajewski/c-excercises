#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>
#include <list>
#include <deque>

int main(int argc, char** argv)
{
	std::deque<std::string> strings(argv, argv+argc);
	
	std::sort(strings.begin(), strings.end());
	
	for(const auto& s : strings)
		std::cout << s << std::endl;
	
}
