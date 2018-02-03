#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <iostream>

namespace bf = boost::filesystem;
namespace bpo = boost::program_options;

uintmax_t fileSize(const bf::path& path)
{
	if (!bf::is_directory(path))
		return bf::file_size(path);

	uintmax_t size = 0;
	for (auto& entry : bf::recursive_directory_iterator(path))
	{
		if (!bf::is_directory(entry.path()))
			size += bf::file_size(entry.path());
	}
	return size;
}

void listDirectory(const std::string& directory, bool extraInfo, bool recursive)
{
	for (auto& entry : bf::directory_iterator(directory))
	{
		auto filename = entry.path().filename().string();
		if (bf::is_directory(entry.path()))
			filename += "/";

		if (extraInfo)
			std::printf("%-30s %8ju\n", filename.c_str(), fileSize(entry.path()));
		else
			std::cout << filename << std::endl;
	}
}

int main(int argc, char** argv)
{
	bool help = false;
	bool extraInfo = false;
	bool recursive = false;
	std::string directory = bf::current_path().string();

	bpo::options_description options{"Options"};
	options.add_options()
		("help,h", bpo::bool_switch(&help), "Show help screen")
		("long,l", bpo::bool_switch(&extraInfo), "Display extra information on each file/directory")
		("tree,t", bpo::bool_switch(&recursive), "Recursively descend into each subdirectory")
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

	listDirectory(directory, extraInfo, recursive);
}
