#include <boost/range/algorithm.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <stdexcept>


/***
Ack Project
Ack allows for grepping for a regex pattern in all files in the entire directory tree.
Add command-line parameters to select different regex styles, case in/sensibility, coloring of output etc.
Get inspired by actual “ack”.

Some first steps:
-l, --files-with-matches
        Only print the filenames of matching files, instead of the matching text.

-L, --files-without-matches
        Only print the filenames of files that do NOT match.
-n, --no-recurse
           No descending into subdirectories.
***/

void read(std::istream& in, std::vector<std::string>& buffer)
{
    std::string line;
    while (std::getline(in, line))
    {
        buffer.push_back(line);
    }
}

void write(std::ostream& out, const std::vector<std::string>& buffer)
{
    for(auto item : buffer)
        out << item << std::endl;
}

int main(int argc, char** argv)
{
    namespace po = boost::program_options;

    bool fname_w_matches = false;
    bool fname_wo_matches = false;
    bool no_recurse = false;
    bool cow = false;

    po::options_description desc("Search files for regex pattern.\nAllowed options:");
    desc.add_options()
        ("help,h", "Show this message")
        ("pattern,p", po::value<std::string>(), "Search for lines matching this regex pattern")
        ("input,i", po::value<std::vector<std::string>>(), "List of paths to search (defaults to current directory)")
        ("output,o", po::value<std::string>(), "output file (defaults to stdout)")
        ("files-with-matches,l", po::bool_switch(&fname_w_matches), "Only print the filenames of matching files, instead of the matching text.")
        ("files-without-matches,L", po::bool_switch(&fname_wo_matches), "Only print the filenames of files that do NOT match.")
        ("no-recurse,n", po::bool_switch(&no_recurse), "No descending into subdirectories.")
        ("cow", po::bool_switch(&cow), "Moo");
    ;

    po::positional_options_description p;
    p.add("pattern", 1).add("input", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    std::string in_files;
    if (vm.count("input"))
    {
        in_files = vm["input"].as<std::vector<std::string>>()[0];
        std::cout << "Searching " << in_files << std::endl;
    }
    else
    {
        in_files = "current dir";
        std::cout << "Searching " << in_files << std::endl;
    }

    std::string search_pattern;
    if (vm.count("pattern"))
    {
        search_pattern = vm["pattern"].as<std::string>();
        std::cout << "Searching for " << search_pattern << std::endl;
    }
    else
    {
        std::cout << desc << std::endl;
        return 1;
    }
    if (cow) {
        std::vector<std::string> cow_pic = {
"         ______",
"        < yolo >",
"         ------",
"              \\   ^__^",
"               \\  (oo)\\_______",
"                  (__)\\       )\\/\\",
"                       ||----w |",
"                       ||     ||"
};
        write(std::cout, cow_pic);
    }
}
