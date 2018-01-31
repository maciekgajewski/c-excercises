#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <iostream>

namespace fs = boost::filesystem;
namespace po = boost::program_options;

struct node_result
{
	std::string output;
	size_t size;
};

node_result* print_contents(const fs::path& path, bool extensive, bool tree, int level = 0)
{
	node_result* result = new node_result();
	std::string name = path.filename().string();
	if (!fs::is_symlink(path))
	{
		if (fs::is_directory(path))
		{
			name += "/";
				for (const auto& it : fs::directory_iterator(path))
				{
					auto child_result = print_contents(it, extensive, tree, level + 1);
					if (extensive) result->size += child_result->size;
					if (tree) result->output += child_result->output;
			}
		}
		else if (extensive) result->size = fs::file_size(path);
	}

	result->output = std::string(level * 2, ' ') + name + (extensive ? ": " + std::to_string(result->size) : "") + "\n" + result->output;
	return result;
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
		std::cout << print_contents(it, extensive, tree)->output;
}
