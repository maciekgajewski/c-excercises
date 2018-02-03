#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <iostream>

namespace bf = boost::filesystem;
namespace bpo = boost::program_options;

int main(int argc, char** argv)
{
	bool help = false;
	bool extraInfo = false;
	bool tree = false;
	std::string directory;

	bpo::options_description options{"Options"};
	options.add_options()
		("help,h", bpo::bool_switch(&help), "Show help screen")
		("long,l", bpo::bool_switch(&extraInfo), "Display extra information on each file/directory")
		("tree,t", bpo::bool_switch(&tree), "Recursively descend into each subdirectory")
		("directory,d", bpo::value<std::string>(&directory), "Working directory");

	boost::program_options::positional_options_description positionalOptions;
	positionalOptions.add("directory", 1);

	bpo::variables_map variablesMap;
	bpo::store(bpo::command_line_parser(argc, argv).options(options).positional(positionalOptions).run(), variablesMap);
	bpo::notify(variablesMap);

	if (help) {
		std::cout << options << std::endl;
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
