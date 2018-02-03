#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <iostream>

namespace bf = boost::filesystem;
namespace bpo = boost::program_options;

int main(int argc, char** argv)
{
	bpo::options_description description{"Options"};
	description.add_options()
		("help,h", "Show help screen");

	bpo::variables_map variablesMap;
	bpo::store(bpo::parse_command_line(argc, argv, description), variablesMap);
	bpo::notify(variablesMap);

	if (variablesMap.count("help")) {
		std::cout << description << std::endl;
		return 1;
	}

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
