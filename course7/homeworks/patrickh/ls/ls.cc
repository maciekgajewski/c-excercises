#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

namespace fs = boost::filesystem;
namespace po = boost::program_options;

class file_summary
{
    public:
        std::string name;
        std::vector<file_summary> summaries;
        size_t size;
};

std::string stringify_summary(const file_summary& summary, bool detailed)
{
    if(summary.size > 0)
    {
        std::string result = summary.name;
        if (detailed)
        {
            result += " [" + std::to_string(summary.size) + "]";
        }

        result += std::string("\n");

        for (const auto &childSum : summary.summaries) {
            result += stringify_summary(childSum, detailed);
        }
        return result;
    }
    else
    {
        return std::string("");
    }
}

file_summary summarize_directory(const fs::path& path, bool detailed, bool tree, int indent)
{
    std::string fileName = "";
    for (auto i = 0; i < indent; i++)
    {
        fileName += "-";
    }

    fileName += path.filename().string();
    file_summary *summary = new file_summary();
    summary->size = 0;
    if(fs::is_directory(path) && tree)
    {
        fileName += "/";
        for(const auto& file : fs::directory_iterator(path))
        {
            file_summary childSum = summarize_directory(file, detailed, tree, indent + 2);
            summary->summaries.push_back(childSum);
            summary->size += childSum.size;
        }
    }
    summary->name = fileName;
    try
    {
        summary->size += fs::file_size(path);
    }
    catch (const fs::filesystem_error& err)
    {
        //catching some file size errors here
    }
    return *summary;
}

int main(int argc, char *argv[])
{
    bool help, tree, detailed = false;
    std::string dir = ".";

    po::positional_options_description positional;
    positional.add("path", 1);
    po::options_description options("Allowed options");
    options.add_options()
            ("long,l", po::bool_switch(&detailed), "extensive mode")
            ("tree,t",po::bool_switch(&tree), "print tree")
            ("path,p", po::value<std::string>(&dir), "active directory")
            ("help,h", po::bool_switch(&help), "print help");
    po::variables_map parameters;
    po::store(po::command_line_parser(argc, argv).options(options).positional(positional).run(), parameters);

    po::notify(parameters);
    if(help)
    {
        std::cout << options << std::endl;
        return 0;
    }

    for (const auto& file : fs::directory_iterator(fs::path(dir)))
    {
        std::cout << stringify_summary(summarize_directory(file, detailed, tree, 0), detailed);
    }
}