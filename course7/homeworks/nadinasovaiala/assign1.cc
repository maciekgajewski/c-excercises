#include <iostream>
#include <boost/filesystem.hpp>

using namespace boost::filesystem;

int main(int argc, char** argv)
{
	path currentPath = current_path();
	for (auto& it : directory_iterator(currentPath))
		std::cout << it.path().filename() << " ";
	std::cout << std::endl;
}
