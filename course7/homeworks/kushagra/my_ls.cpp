#include <iostream>
#include <boost/filesystem.hpp>

int main(int argc, char** argv)
{
	boost::filesystem::path full_path(boost::filesystem::current_path());
    if (argc > 1) {
        boost::filesystem::path new_path(argv[1]);
		full_path.swap(new_path) ;
    }
	
    try {
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
        else {
            std::cout << full_path << std::endl;
        }
    }
    catch (const boost::filesystem::filesystem_error& exception) {
        std::cout << exception.what() << std::endl; 
    }
    return 0;
}
