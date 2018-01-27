#include <iostream>
#include <boost/filesystem.hpp>

int main()
{
	std::string path (".");
	if (boost::filesystem::is_directory(path))
	{
		for (boost::filesystem::directory_iterator iterator(path); iterator!=boost::filesystem::directory_iterator(); ++iterator)
		{
			std::cout << iterator->path().filename() << std::endl;
		}
	}
}