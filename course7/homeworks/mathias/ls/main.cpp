#include <boost/filesystem.hpp>
#include <boost/optional.hpp>
#include <boost/program_options.hpp>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

class Node
{
public:
	static Node buildRootNode(const boost::filesystem::path& path, bool attributes)
	{
		auto node = Node(path);
		node.processNode(attributes);
		return node;
	}

	void print(bool asTree, size_t indentationLevel = 0u) const
	{
		if (mFileSize.is_initialized() && indentationLevel == 0u)
		{
			std::cout << "total";
			printAttributes();
			std::cout << std::endl;
		}

		for (const auto& node : mChildren)
		{
			std::cout << std::string(indentationLevel * 2, ' ') << node.mPath.filename().string();

			if (node.mIsDirectory)
			{
				std::cout << "/";

				node.printAttributes();
				std::cout << std::endl;

				if (asTree)
					node.print(asTree, indentationLevel + 1);
			}
			else
			{
				node.printAttributes();
				std::cout << std::endl;
			}
		}
	}

private:
	Node(const boost::filesystem::path& path)
		: mPath(path)
		, mIsDirectory(boost::filesystem::is_directory(path))
	{}

	void printAttributes() const
	{
		if (mFileSize.is_initialized())
		{
			std::cout << " " << *mFileSize;
		}
	}

	void processNode(bool attributes)
	{
		if (mIsDirectory)
		{
			for (const auto& entry : boost::filesystem::directory_iterator(mPath))
			{
				auto node = Node(entry.path());
				node.processNode(attributes);
				mChildren.push_back(std::move(node));
			}
		}

		if (attributes)
			readAttributes();
	}

	void readAttributes()
	{
		if (mIsDirectory)
		{
			mFileSize = std::accumulate<std::vector<Node>::iterator, std::uintmax_t>(mChildren.begin(), mChildren.end(), 0u,
				[](auto size, const auto& node)
				{
					return size + (node.mFileSize.is_initialized() ? node.mFileSize.value() : 0u);
				});
		}
		else
		{
			mFileSize = boost::filesystem::file_size(mPath);
		}
	}

	boost::filesystem::path mPath;
	bool mIsDirectory;
	std::vector<Node> mChildren;
	boost::optional<std::uintmax_t> mFileSize;
};

int main(int argc, char** argv)
{
	bool asTree, attributes;
	std::string directory;

	boost::program_options::options_description desc("ls options");
	desc.add_options()
		("help,h", "this message")
		("tree,t", boost::program_options::bool_switch(&asTree)->default_value(false), "show directory tree")
		("long,l", boost::program_options::bool_switch(&attributes)->default_value(false), "use long listing format")
		("directory,d", boost::program_options::value<std::string>(&directory)->default_value("."), "directory")
	;

	boost::program_options::positional_options_description positionalDesc;
	positionalDesc.add("directory", 1);

	boost::program_options::variables_map vars;
	try
	{
		boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).positional(positionalDesc).run(), vars);
		boost::program_options::notify(vars);
	}
	catch (const boost::program_options::error& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	if (vars.count("help"))
	{
		std::cout << "Usage: ls [Options] [Dir]" << std::endl;
		std::cout << desc << std::endl;
		return 0;
	}

	boost::filesystem::path path(directory);

	if (!boost::filesystem::exists(path))
	{
		std::cout << "Could not find " << path << std::endl;
		return 1;
	}

	if (!boost::filesystem::is_directory(path))
	{
		std::cout << path << " is not a directory" << std::endl;
		return 2;
	}
	
	auto rootNode = Node::buildRootNode(path, attributes);
	rootNode.print(asTree);

	return 0;
}
