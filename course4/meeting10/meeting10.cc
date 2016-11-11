#include <iostream>
#include <map>
#include <unordered_set>
#include <string>

int main(int argc, char** argv)
{
	std::map<std::string, int> arg_counts;
	for(int i = 0; i < argc; i++)
		arg_counts[argv[i]]++;
	
	for(const auto& p : arg_counts)
		std::cout << p.first << " : " << p.second << std::endl;
}

