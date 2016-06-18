
#include "linked-list.h"

#include <boost/program_options.hpp>

#include <iostream>
#include <string>
#include <algorithm>

int main(int argc, char** argv)
{
    boost::program_options::options_description desc("Allowded Options");
    
    desc.add_options()
    ("help", "Show Help")
    ("Other", "Other stuff");
    
    boost::program_options::variables_map args;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), args);
    boost::program_options::notify(args);
    
    if (args.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }
    
    LinkedList<int> v{ 2, 4, 2, 0, 5, 10, 7, 3, 7, 1 };

   // std::rotate(v.begin(), v.begin()++, v.end());

    LinkedList<int> items;
    std::fill_n(std::front_inserter(items), 3, -1);
    std::cout << "Strings in the list are: ";
    bool isFirst = true;
    for (auto element : items)
    {
        if(!isFirst)
        {
            std::cout << ", ";
        }
		std::cout << element;
        isFirst = false;
    }
    std::cout << std::endl;    
    
    return 0;
}
