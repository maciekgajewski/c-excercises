#include <boost/filesystem.hpp>
#include <string>
#include <iostream>

namespace fs = boost::filesystem;


int main(int argc, char** argv)
{
    std::string path_name = "";
    if (argc > 1) {
        path_name = argv[1];
    }
	fs::path full_path(path_name);
	
    if (fs::exists(full_path)) {
        if (fs::is_regular_file(full_path)) {
            std::cout << full_path << std::endl;
        }
        else {
            for (fs::directory_entry& x : fs::recursive_directory_iterator(full_path)) {
                std::cout << "\t" << x.path().generic_string() << std::endl;
            } 
        } 
    }
}
