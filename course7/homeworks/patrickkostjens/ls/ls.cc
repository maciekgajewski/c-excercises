#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <iostream>

namespace fs = boost::filesystem;
namespace po = boost::program_options;

std::map<const std::string, size_t> cache;
size_t get_size(const fs::path& path)
{
	const std::string path_string = path.string();
	if (cache.count(path_string)) return cache.at(path_string);

	size_t size = 0;
	if (fs::is_directory(path))
		for (const auto& it : fs::directory_iterator(path)) 
			size += get_size(it);
	else
		size = fs::file_size(path);

	cache.insert(std::pair<const std::string, size_t>(path_string, size));
	return size;
}

void print_contents(const fs::path& path, bool extensive, bool tree, int level = 0)
{
	bool is_directory = fs::is_directory(path);

	std::cout << std::string(level * 2, ' ') << path.filename().string();
	if (is_directory) std::cout << "/";
	if (extensive) std::cout << ": " << get_size(path);
	std::cout << std::endl;

	if (is_directory && tree)
		for (const auto& it : fs::directory_iterator(path))
			print_contents(it, extensive, tree, level + 1);
}

int main(int argc, char** argv)
{
	std::string directory;
	bool extensive, tree;
	po::options_description options("Allowed options");
	options.add_options()
		("help,h", "print help message")
		("long,l", po::bool_switch(&extensive), "show extend file and directory information")
		("tree,t", po::bool_switch(&tree), "print file tree recursively")
		("directory,d", po::value<std::string>(&directory)->default_value("."), "directory to list");

	po::positional_options_description positional;
	positional.add("directory", 1);

	po::variables_map parameters;
	po::store(po::command_line_parser(argc, argv).options(options)
		.positional(positional).run(), parameters);

	if (parameters.count("help"))
	{
		std::cout << options;
		return 0;
	}
	po::notify(parameters);

	const fs::path path(directory);
	for (const auto& it : fs::directory_iterator(path))
		print_contents(it, extensive, tree);
}
