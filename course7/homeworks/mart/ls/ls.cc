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

void listDirectory(const bf::path& directory, bool extraInfo, bool recursive, uint32_t level = 0)
{
	for (auto& entry : bf::directory_iterator(directory))
	{
		std::stringstream filename;
		for (uint32_t i = 0; i < level; i++)
			filename << "  ";

		filename << entry.path().filename().string();
		if (bf::is_directory(entry.path()))
			filename << "/";

		if (extraInfo)
		{
			try
			{
				filename << " [" << fileSize(entry.path()) << "]";
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
		}

		std::cout << filename.str().c_str() << std::endl;

		if (bf::is_directory(entry.path()))
			listDirectory(entry.path(), extraInfo, recursive, level + 1);
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

	if (help)
	{
		std::cout << options << std::endl;
		return 1;
	}

	if (!bf::exists(directory) || !bf::is_directory(directory))
	{
		std::cerr << "Given path is not valid directory" << std::endl;
		return 1;
	}
	listDirectory(directory, extraInfo, recursive);
}
