#include "simple_string.h"
#include <memory>
#include <string>

using namespace simple_string;

String::String() = default;

String::String(const char* initString)
{
    size = std::strlen(initString) + 1;
    buffer = std::make_unique<char[]>(size);
    std::strcpy(buffer.get(), initString);
}

// String::String(const String& src) // copy
//
// String::String(String&& src) // move


void String::Print() const
{
    if (buffer)
    {
        std::cout << '"';
        for (auto i = 0; i < size; i++)
        {
            std::cout << buffer[i];
        }
        std::cout << '"';
        std::cout << std::endl;
    }
    else
    {
        std::cout << '"' << '"' << std::endl;
    }
}

int String::Length() const
{
    return size;
    // if (buffer)
        // return *buffer.strlen();
    // else
    //     return 0;
}
