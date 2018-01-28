#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <string>
#include <sstream>
#include <iostream>

namespace bpo = boost::program_options;
namespace bfs = boost::filesystem;

unsigned int fileSize(const bfs::path& path)
{
	if (!bfs::exists(path))
		throw std::runtime_error("File doesn't exist");

	if (bfs::is_regular_file(path))
	{
		return bfs::file_size(path);
	}
	unsigned int result = 0;

	bfs::directory_iterator currDir(path);

	for (const auto& it : currDir)
	{
		result += fileSize(it.path());
	}
	return result;
}

std::string treeTraversal(const bfs::path& path, const bool& treeArg, const bool& longArg, unsigned int indentLevel = 0)
{
	if (!bfs::exists(path))
		throw std::runtime_error("File doesn't exist");

	std::stringstream ss;
	for (unsigned int i = 0; i < indentLevel; i++)
	{
		ss << "  ";
	}

	ss << path.filename().string();

	if (bfs::is_directory(path))
		ss << "/";

	if (longArg)
	{
		ss << "\t" << fileSize(path);
	}

	ss << std::endl;

	if (treeArg && bfs::is_directory(path))
	{
		bfs::directory_iterator currDir(path);

		for (const auto& it : currDir)
		{
			ss << treeTraversal(it.path(), treeArg, longArg, indentLevel + 1);
		}
	}

	return ss.str();
}

std::string list(const bfs::path& path, const bool& treeArg, const bool& longArg)
{
	std::stringstream ss;
	if (bfs::is_regular_file(path))
	{
		ss << treeTraversal(path, treeArg, longArg);
	}
	else
	{
		bfs::directory_iterator currDir(path);

		for (const auto& it : currDir)
		{
			ss << treeTraversal(it.path(), treeArg, longArg);
		}
	}
	return ss.str();
}

int main(int argc, char** argv)
{
	bool longArg;
	bool treeArg;

	bpo::options_description desc;
	desc.add_options()
		("help,h", "Help message")
		("long,l", bpo::bool_switch(&longArg)->default_value(false), "Print more information")
		("tree,t", bpo::bool_switch(&treeArg)->default_value(false), "Recursively iterate through filesystem")
		("path", bpo::value<std::string>(), "Path")
		;
	bpo::positional_options_description pod;
	pod.add("path", -1);

	bpo::variables_map vm;
	bpo::store(bpo::command_line_parser(argc, argv).options(desc).positional(pod).run(), vm);
	bpo::notify(vm);

	if (vm.count("help"))
	{
		std::cout << desc << std::endl;
		return 1;
	}

	bfs::path currPath;
	if (vm.count("path"))
	{
		currPath = boost::filesystem::path(vm["path"].as<std::string>());
	}
	else
	{
		currPath = boost::filesystem::current_path();
	}

	if (!bfs::exists(currPath))
	{
		throw std::runtime_error("File not found!");
	}
	std::cout << list(currPath, treeArg, longArg);

	return 0;
}
