#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <string>
#include <tuple>
#include <iostream>

namespace po = boost::program_options;
namespace fs = boost::filesystem;

void print_dir_contents(fs::path full_path, std::string spaces) {
    if (fs::is_regular_file(full_path)) {
        std::cout << spaces << full_path.filename() << std::endl;
    }
    else {
        for (fs::directory_entry& x : fs::directory_iterator(full_path)) {
            std::cout << spaces << x.path().generic_string() << fs::path::preferred_separator
                     << std::endl;
            spaces += "\t";
            print_dir_contents(x, spaces);
        } 
    } 
}


// std::cout << spaces << boost::file_size(full_path) << "\t" << full_path.generic_string() << std::endl;


void print_dir_contents(fs::path full_path) {
    if (fs::is_regular_file(full_path)) {
        std::cout << "\t" << full_path.filename() << std::endl;
    }
    else {
        for (fs::directory_entry& x : fs::directory_iterator(full_path)) {
            if (fs::is_regular_file(x.path())) {
                std::cout << "\t\t" << x.path().filename() << std::endl;
            } else {
                std::cout << "\t" << x.path().generic_string() << fs::path::preferred_separator
                    << std::endl;
            }
        } 
    } 
}


int main(int argc, char** argv)
{
    po::options_description desc("Display contents of a directory with ");
    desc.add("path", -1);
    desc.add_options()
        ("path,p", value<std::string>()->default_value("."), "Path to display")
        ("long,l", value<bool>()->default_value(false), "Display full details")
        ("tee,t", value<bool>()->default_value(false), "Recursively display directory contents")
        ("help,h", "Display help text");
    po::variables_map vm;
    std::string spaces = "\t";
    std::string path_name = ".";
	fs::path full_path(path_name);
	
    if (fs::exists(full_path)) {
        if (details) {
            print_dir_contents(full_path, spaces);
        } else {
            print_dir_contents(full_path, spaces);
        }
    }
}
