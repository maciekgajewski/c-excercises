#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <string>
#include <tuple>
#include <iostream>

namespace po = boost::program_options;
namespace fs = boost::filesystem;


//For directory display without details
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


//Function overloading. For recursive directory display without details
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


/*
Calculate the size of the files in the directory. If recursive is set to true, the total size of all files in the
directory and its subdirectories. If set to false, only the size of the files in the directory is calculated and
returned.
*/
int get_dir_size(fs::path dir_path, bool recursive=false) {
    int dir_size = 0;
	if(recursive) {
		for (fs::directory_entry& x : fs::recursive_directory_iterator(dir_path)) {
			if (fs::is_regular_file(x)) {
				dir_size += fs::file_size(x);
			}
		}
	} else {
		for (fs::directory_entry& x : fs::directory_iterator(dir_path)) {
			if (fs::is_regular_file(x)) {
				dir_size += fs::file_size(x);
			}
		}
	}
	return dir_size;
}


/*Display the directory contents, along with the sizes. The size of the directory is calculated by the sum of all
the sizes of immediate descendant files in the directory
*/
void print_detailed_dir_contents(fs::path display_path) {
	int file_size = 0;
	int dir_size = get_dir_size(display_path);
	std::cout << std::to_string(dir_size) << "\t" << display_path.filename().generic_string()
			  << fs::path::preferred_separator << std::endl;
	for (fs::directory_entry& x : fs::directory_iterator(display_path)) {
		if (fs::is_regular_file(x.path())) {
			file_size = fs::file_size(x.path());
			std::cout << "\t" << std::to_string(file_size) << "\t" << x.path().filename().string() << std::endl;
		}
		else {
			dir_size = get_dir_size(x.path());
			std::cout << "\t" << std::to_string(dir_size) << "\t" << x.path().filename().generic_string()
					  << fs::path::preferred_separator << std::endl;
		}
    }
}


/*Display the directory contents, along with the sizes. The size of the directory is calculated by the sum of all
the sizes of immediate descendant files in the directory, as well as its subdirectories.
*/
void print_detailed_dir_contents(fs::path display_path, std::string spaces) {
	int dir_size = 0;
	int file_size = 0;
	if (fs::is_regular_file(display_path)) {
		file_size = fs::file_size(display_path);
		std::cout << spaces << std::to_string(file_size) << "\t" << display_path.filename().string() << std::endl;
	}
    else {
		dir_size = get_dir_size(display_path, true);
        std::cout << spaces << std::to_string(dir_size) << "\t" << display_path.filename().generic_string()
				  << fs::path::preferred_separator << std::endl;
        spaces += "\t";
        for (fs::directory_entry& x : fs::directory_iterator(display_path)) {
            print_detailed_dir_contents(x.path(), spaces);
        }
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
