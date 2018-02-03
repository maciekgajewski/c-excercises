#include <boost/filesystem.hpp>
#include <iostream>

int main(int argc, char** argv)
{
	auto current_path = boost::filesystem::current_path();

	for (auto& entry : boost::filesystem::directory_iterator(current_path))
	{
		auto filename = entry.path().filename();
		std::cout << filename.string() << std::endl;
	}
}
