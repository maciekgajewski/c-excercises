#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <iostream>

namespace bf = boost::filesystem;
namespace bpo = boost::program_options;

int main(int argc, char** argv)
{
	bool help = false;

	bpo::options_description options{"Options"};
	options.add_options()
		("help,h", bpo::bool_switch(&help), "Show help screen");

	bpo::variables_map variablesMap;
	bpo::store(bpo::command_line_parser(argc, argv).options(options).run(), variablesMap);
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
