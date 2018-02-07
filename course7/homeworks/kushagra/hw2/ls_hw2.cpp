#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <string>
#include <tuple>
#include <iostream>

namespace po = boost::program_options;
namespace fs = boost::filesystem;


void print_dir_contents(fs::path display_path, std::string spaces) {
    if (fs::is_regular_file(display_path)) {
        std::cout << spaces << display_path.filename().generic_string() << std::endl;
    }
    else {
        std::cout << spaces << display_path.filename().generic_string() <<
            fs::path::preferred_separator << std::endl;
        spaces += "\t";
        for (fs::directory_entry& x : fs::directory_iterator(display_path)) {
            print_dir_contents(x.path(), spaces);
        } 
    } 
}


// std::cout << spaces << boost::file_size(full_path) << "\t" << full_path.generic_string() << std::endl;


void print_dir_contents(fs::path full_path) {
    std::cout << full_path.generic_string() << fs::path::preferred_separator << std::endl;
    for (fs::directory_entry& x : fs::directory_iterator(full_path)) {
        if (fs::is_regular_file(x.path())) {
            std::cout << "\t" << x.path().filename().string() << std::endl;
        } else {
            std::cout << "\t" << x.path().filename().generic_string() << fs::path::preferred_separator
                << std::endl;
        }
    } 
}


void print_detailed_dir_contents(fs::path full_path) {
    int dir_size = 0;
    std::vector<std::string> file_vector;
    for (fs::directory_entry& x : fs::directory_iterator(full_path)) {
        if (fs::is_regular_file(x.path())) {
            int file_size = fs::file_size(x.path());
            dir_size += file_size;
            file_vector.push_back("\t" + std::to_string(file_size) + "\t" + x.path().filename().string());
        } else {
            file_vector.push_back("\t0\t" + x.path().filename().generic_string() + fs::path::preferred_separator);
        }
    }
    std::cout << std::to_string(dir_size) << "\t" << full_path.generic_string() <<
        fs::path::preferred_separator << std::endl;
    for (std::string& s : file_vector) {
        std::cout << s << std::endl;
    }
}


void print_detailed_dir_contents(fs::path display_path, std::string spaces) {
    int* file_sizes = 0;
    std::vector<std::string> v;
    if (fs::is_regular_file(display_path)) {
        int file_size = fs::file_size(display_path);
        v.push_back(spaces + std::to_string(file_size) + "\t" + display_path.filename().generic_string());
        *file_sizes += file_size;
    }
    else {
        spaces += "\t";
        for (fs::directory_entry& x : fs::directory_iterator(display_path)) {
            print_dir_contents(x.path(), spaces);
        }
        v.push_back(spaces + std::to_string(*file_sizes) +  "\t" + display_path.filename().generic_string() +
                        fs::path::preferred_separator);
    }
}


int main(int argc, char** argv)
{
	std::string path_name = ".";
	bool details = false, recursive = false;
	
    po::options_description desc("Display contents of a directory.");
    desc.add_options()
        ("help,h", "Display help text")
        ("path_name,p", po::value<std::string>()->default_value("."), "Path to display")
        ("long,l", po::bool_switch()->default_value(false)->implicit_value(true),
			"Display full details")
        ("tee,t", po::bool_switch()->default_value(false)->implicit_value(true),
			"Recursively display directory contents");
	po::positional_options_description posOption;
    posOption.add("path_name", -1);
    po::variables_map vm;
	po::store(po::command_line_parser(argc, argv).options(desc).positional(posOption).run(), vm);
	po::notify(vm);

	if(vm.count("path_name")) {
		path_name = vm["path_name"].as<std::string>();
		if (path_name.back() == '/') {
			path_name.erase(path_name.length()-1);
		}
	}
	if(vm.count("long")) {
		details = vm["long"].as<bool>();
	}
	if(vm.count("tee")) {
		recursive = vm["tee"].as<bool>();
	}
	if(vm.count("help")) {
        std::cout << desc << std::endl; 
       return 0;
	}
	
	fs::path full_path(path_name);
    if (fs::exists(full_path)) {
		if (fs::is_regular_file(full_path)) {
            if(details) {
                std::cout << fs::file_size(full_path) << "\t";
            }
			std::cout << full_path.generic_string() << std::endl;
		}
		else {
			std::string spaces = "";
            if (details) {
                if (recursive) {
                    print_detailed_dir_contents(full_path, spaces);
                } else {
                    print_detailed_dir_contents(full_path);
                }
            } else {
                if (recursive) {
                    print_dir_contents(full_path, spaces);
                } else {
                   print_dir_contents(full_path);
                }
            }
		}
    }
}
