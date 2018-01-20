#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ls [dir]" << std::endl;
		return 0;
	}

	boost::filesystem::path path(argv[1]);

	if (!boost::filesystem::exists(path))
	{
		std::cout << "Could not find " << path << std::endl;
		return 1;
	}

	if (!boost::filesystem::is_directory(path))
	{
		std::cout << path << " is not a directory" << std::endl;
		return 2;
	}

	std::vector<std::string> entries;
	for (const auto& entry : boost::filesystem::directory_iterator(path))
	{
		entries.emplace_back(entry.path().filename().string());
	}
	
	std::sort(std::begin(entries), std::end(entries));
	for (const auto& entry : entries)
	{
		std::cout << entry << std::endl;
	}

	return 0;
}
