#include <iostream>
#include <unordered_map>
#include <string>

#include <set>

using namespace std::literals;

int main(int argc, char** argv)
{
	std::set<std::string> s(argv+1, argv+argc);
	
//	auto it = s.find("Waldo");
//	if (it != s.end())
	if(s.count("Waldo") > 0)
		std::cout << "Waldo is in the house!" << std::endl;

		
	for(const auto& x : s)
		std::cout << x << std::endl;
}
