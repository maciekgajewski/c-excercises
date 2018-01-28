#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <algorithm>
#include <iomanip>
#include <iostream>

namespace fs = boost::filesystem;
namespace po = boost::program_options;

struct configuration
{
    std::string file_path = ".";
    bool show_help = false;
    bool show_tree = false;
    bool show_long = false;
};

configuration parse_args(int argc, char *argv[]);
void print_file_tree(const fs::path& dir, const configuration& config, const std::string& filler = "");
size_t get_file_size(const fs::path&);

int main(int argc, char *argv[])
{
    try
    {
        const configuration& config = parse_args(argc, argv);

        if (!config.show_help)
        {
            fs::path path(config.file_path);
            print_file_tree(path, config);
        }

        return 0;
    }
    catch(std::exception& ex)
    {
        std::cout << "\033[1;31m" << ex.what() << "\033[0m" << std::endl;
        return 1;
    }
}

configuration parse_args(int argc, char *argv[])
{
    configuration config;
    po::positional_options_description po;
    po.add("file", 1);

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", po::bool_switch(&config.show_help), "show help")
        ("tree,t", po::bool_switch(&config.show_tree), "show tree")
        ("long,l", po::bool_switch(&config.show_long), "show long")
        ("file", po::value<std::string>(&config.file_path), "file path")
    ;

    auto print_help = [&]
    {
        fs::path p(argv[0]);
        std::cout << "Usage: " << p.filename().string() << " [OPTION]... [FILE]" << std::endl << std::endl;
        std::cout << desc << std::endl;
    };

    try
    {
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(po).run(), vm);
        po::notify(vm);

        if (config.show_help)
            print_help();
    }
    catch(boost::exception& ex)
    {
        print_help();
        throw;
    }

    return config;
}

void print_file_info(const fs::path& file, const configuration& config, const std::string& filler)
{
    std::cout << filler;

    if (config.show_long)
    {
        if (config.show_tree)
            std::cout << std::setfill('.');

        std::cout << std::left << std::setw(12) << get_file_size(file);
    }

    std::cout << file.filename().string();

    if (fs::is_directory(file))
        std::cout << fs::path::preferred_separator;
    std::cout << std::endl;
}

std::string get_increased_filler(const std::string filler)
{
    const static std::string& filler_diff = "    ";
    return filler + filler_diff;
}

void print_file_tree(const fs::path& dir, const configuration& config, const std::string& filler)
{
    for(auto& file: fs::directory_iterator(dir))
    {
        print_file_info(file, config, filler);

        if (config.show_tree && fs::is_directory(file) && !fs::is_symlink(file))
            print_file_tree(file, config, get_increased_filler(filler) );
    }
}

size_t get_file_size(const fs::path& fp)
{
    size_t size = 0;

    if (fs::is_directory(fp) && !fs::is_symlink(fp))
    {
        for(auto& subfile: fs::directory_iterator(fp))
        {
            size += get_file_size(subfile);
        }
    }
    else if (fs::is_regular_file((fp)))
    {
        size = fs::file_size(fp);
    }

    return size;
}
