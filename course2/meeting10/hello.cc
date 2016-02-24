#include <iostream>

#include <algorithm>
#include <vector>
#include <set>
#include <map>

#include <boost/range/algorithm.hpp>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Requires param" << std::endl;
        return 1;
    }
    std::map<int, std::string> data = {{1, "one"}, {4, "four"}};
    
    auto it = data.begin();
    
    try
    {
        int search = std::stoi(argv[1]);
        std::cout << "Looking for a number: " << search << std::endl;
        it = data.find(search); // O(log(n))
    }
    catch(...)
    {
        std::string search = argv[1];
        std::cout << "Looking for a string: " << search << std::endl;
        
        it = boost::find_if(data,
            [&](const auto& pair)
            {
                return pair.second == search;
            }); // O(n)
    }
        
    if (it == data.end())
    {
        std::cout << "value not found" << std::endl;
    }
    else
    {
        std::cout << "Found!!! key=" << it->first << ", val=" << it->second << std::endl;
    }
        
}