#include <boost/filesystem.hpp>

#include <iostream>

int main(int argc, char** argv)
{
	boost::filesystem::path currPath = boost::filesystem::current_path();
	boost::filesystem::directory_iterator currDir(currPath);

	for (const auto& it : currDir)
	{
		std::cout << it.path().filename() << std::endl;
	}

	return 0;
}
