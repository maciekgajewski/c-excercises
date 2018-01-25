#include <boost/filesystem.hpp>
#include <iostream>

int main(int argc, char** argv)
{
	boost::filesystem::path current_directory(argc >= 2 ? argv[1] : ".");

	boost::filesystem::directory_iterator dir_iterator(current_directory);
	for (const auto it : dir_iterator)
	{
		std::cout << it.path().filename().string() << std::endl;
	}
}
