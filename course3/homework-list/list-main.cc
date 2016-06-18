
#include "linked-list.h"

#include <iostream>
#include <string>
#include <algorithm>

int main(int argc, char** argv)
{
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
