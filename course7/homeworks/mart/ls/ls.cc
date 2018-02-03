#include <boost/filesystem.hpp>
#include <iostream>

namespace bf = boost::filesystem;

int main(int argc, char** argv)
{
	auto current_path = bf::current_path();

	for (auto& entry : bf::directory_iterator(current_path))
	{
		auto filename = entry.path().filename();
		std::cout << filename.string();
		if (bf::is_directory(entry.path()))
			std::cout << "/";
		std::cout << std::endl;
	}
}
