#include <iostream>
#include <boost/filesystem.hpp>

int main(int argc, char** argv)
{
	boost::filesystem::path current_directory(argc >= 2 ? argv[1] : ".");

	boost::filesystem::directory_iterator end;
	for (boost::filesystem::directory_iterator itr(current_directory); itr != end; ++itr) 
	{
		std::cout << itr->path().filename().string() << std::endl;
	}
}
