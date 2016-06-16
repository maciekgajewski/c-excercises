
#include "linked-list.h"

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    LinkedList<std::string> strings;
    strings.push_front("strings");
    strings.push_front("of");
    strings.push_front("list");
    strings.push_front("A");
    
    std::cout << "Strings in the list are: ";
    bool isFirst = true;
    for(auto element : strings)
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
