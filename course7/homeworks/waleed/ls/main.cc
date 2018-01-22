#include <boost/filesystem.hpp>

#include <iostream>

int main(int argc, char** argv)
{
	boost::filesystem::path CurrPath = boost::filesystem::current_path();
	boost::filesystem::directory_iterator CurrDir(CurrPath);

	for (const auto& it : CurrDir)
	{
		std::cout << it.path().filename() << std::endl;
	}

	return 0;
}
