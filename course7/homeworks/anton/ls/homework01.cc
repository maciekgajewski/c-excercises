#include <boost/filesystem.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    boost::filesystem::path path(".");

    for(auto& dir_entry: boost::filesystem::directory_iterator(path))
    {
        std::cout << dir_entry.path().filename().string() << std::endl;
    }

    return 0;
}
