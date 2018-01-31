#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <string>
#include <iostream>


int main(int argc, char** argv)
{
	boost::filesystem::path full_path(boost::filesystem::current_path());
    if (argc > 1) {
        boost::filesystem::path full_path(argv[1]);
    }
	
    if (boost::filesystem::exists(full_path)) {
        if (boost::filesystem::is_regular_file(full_path)) {
            std::cout << full_path << std::endl;
        }
        else {
            for (boost::filesystem::directory_entry& x : boost::filesystem::directory_iterator(full_path)) {
                std::cout << "\t" << x.path() << std::endl;
            } 
        } 
    }
}
