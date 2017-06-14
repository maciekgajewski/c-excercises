#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <regex>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


/***
Ack Project
Ack allows for grepping for a regex pattern in all files in the entire directory tree.
Add command-line parameters to select different regex styles, case in/sensibility, coloring of output etc.
Get inspired by actual “ack”.

Next steps:
* Search stdin
* actually write to file if desired
* colors
***/

void find_matching_lines(const boost::filesystem::directory_entry& fs_entry, const std::regex& pattern, std::vector<std::string>& match_buffer)
{
    std::ifstream infile(fs_entry.path().string());
    if (infile)
    {
        std::string line;
        int line_no = 0;
        std::smatch match;
        std::string to_print;
        while (std::getline(infile, line))
        {
            line_no++;
            if (std::regex_search(line, match, pattern)) {
                to_print = std::to_string(line_no) + ":" + line;
                match_buffer.push_back(to_print);

            }
        }
    }
    else
    {
        std::string msg = std::strerror(errno);
        throw std::runtime_error("Failed to open file: " + msg);
    }
}


void write(std::ostream& out, const std::string& line)
{
    out << line << std::endl;
}


void write(std::ostream& out, const std::vector<std::string>& buffer)
{
    for(auto item : buffer)
        out << item << std::endl;
}


int main(int argc, char** argv)
{
    namespace po = boost::program_options;
    namespace bfs = boost::filesystem;

    bool fname_w_matches = false;
    bool fname_wo_matches = false;
    bool no_recurse = false;
    bool cow = false;

    po::options_description desc("Search files for regex pattern.\nAllowed options:");
    desc.add_options()
        ("help,h", "Show this message")
        ("pattern,p", po::value<std::string>(), "Search for lines matching this regex pattern")
        ("search_paths,s", po::value<std::vector<std::string>>(), "List of paths to search (defaults to current directory)")
        ("output,o", po::value<std::string>(), "output file (defaults to stdout)")
        ("files-with-matches,l", po::bool_switch(&fname_w_matches), "Only print the filenames of matching files, instead of the matching text.")
        ("files-without-matches,L", po::bool_switch(&fname_wo_matches), "Only print the filenames of files that do NOT match.")
        ("no-recurse,n", po::bool_switch(&no_recurse), "No descending into subdirectories.")
        ("cow", po::bool_switch(&cow), "Moo");
    ;

    po::positional_options_description p;
    p.add("pattern", 1).add("search_paths", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    std::vector<std::string> input_search_paths;
    std::vector<bfs::directory_entry> paths_to_process;
    if (vm.count("search_paths"))
    {
        input_search_paths = vm["search_paths"].as<std::vector<std::string>>();
    }
    else
    {
        input_search_paths = {"."};
    }
    for (std::string path : input_search_paths)
    {
        if (!bfs::exists(path))
        {
            throw std::runtime_error("Path does not exist: " + path);
        }
        else if (bfs::is_regular_file(path))
        {
            paths_to_process.emplace_back(path);
        }
        else if (bfs::is_directory(path) && no_recurse)
        {
            for (bfs::directory_entry& bfs_path : bfs::directory_iterator(path))
            {
                if (bfs::is_regular_file(bfs_path))
                    paths_to_process.push_back(bfs_path);
            }
        }
        else if (bfs::is_directory(path))
        {
            for (bfs::directory_entry& bfs_path : bfs::recursive_directory_iterator(path))
            {
                if (bfs::is_regular_file(bfs_path))
                    paths_to_process.push_back(bfs_path);
            }
        }
        else
        {
            throw std::runtime_error("Path is not a regular file or a directory: " + path);
        }
    }

    std::regex search_pattern;
    if (vm.count("pattern"))
    {
        search_pattern = std::regex(vm["pattern"].as<std::string>());
    }
    else if (! cow)
    {
        std::cout << desc << std::endl;
    }

    for (bfs::directory_entry& bfs_path : paths_to_process)
    {
        std::vector<std::string> match_buffer;
        find_matching_lines(bfs_path, search_pattern, match_buffer);
        if (fname_w_matches)
        {
            if (match_buffer.size())
                write(std::cout, bfs_path.path().string());
        }
        else if (fname_wo_matches)
        {
            if (!match_buffer.size())
                write(std::cout, bfs_path.path().string());
        }
        else if (match_buffer.size())
        {
            write(std::cout, bfs_path.path().string());
            write(std::cout, match_buffer);
            write(std::cout, "\n");
        }
    }

    if (cow)
    {
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
