#include <boost/filesystem.hpp>

#include <iostream>
#include <algorithm>
#include <iterator>

int main(int /*argc*/, char** /*argv*/)
{
	std::cout << "Hello, world!" << std::endl;
	
	namespace bfs = boost::filesystem;
	
	std::copy(
			bfs::recursive_directory_iterator("."),
			bfs::recursive_directory_iterator(), 
			std::ostream_iterator<bfs::directory_entry>(std::cout, ", "));
}


