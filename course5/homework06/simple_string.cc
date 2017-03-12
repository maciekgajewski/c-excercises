#include "simple_string.h"
#include <memory>
#include <string>
#include <stdexcept>


using namespace simple_string;

String::String() = default;

String::String(const char* initString)
{
    size = std::strlen(initString) + 1;
    buffer = std::make_unique<char[]>(size);
    std::strcpy(buffer.get(), initString);
}

String::String(const String& src) // copy
{
    size = src.size;

    if (src.buffer)
    {
        buffer = std::make_unique<char[]>(size);
        for (auto i = 0; i < size; i++)
        {
            buffer[i] = src.buffer[i];
        }
    }
}

String::String(String&& src) // move
{
    buffer = std::move(src.buffer);
    size = src.size;

    src.buffer = nullptr;
    src.size = 0;
}
String& String::operator=(const String& src) // copy assignment
{
    size = src.size;
    if (src.buffer)
    {
        buffer = std::make_unique<char[]>(size);
        for (auto i = 0; i < size; i++)
        {
            buffer[i] = src.buffer[i];
        }
    }
    else
    {
        buffer = nullptr;
    }

    return *this;
}

String& String::operator=(String&& src) // move assignment
{
    buffer = std::move(src.buffer);
    size = src.size;

    src.buffer = nullptr;
    src.size = 0;

    return *this;
}

String& String::operator=(const char * src) // assignment from const char *
{
    size = std::strlen(src) + 1;
    buffer = std::make_unique<char[]>(size);
    std::strcpy(buffer.get(), src);

    return *this;
}

char String::operator[](const int i) const
{
    if (buffer && i < size)
        return buffer[i];
    else
        throw std::runtime_error("Index error: '" + std::to_string(i) + "' is out of range.");
}

char& String::operator[](const int i)
{
    if (buffer && i < size)
        return buffer[i];
    else
        throw std::runtime_error("Index error: '" + std::to_string(i) + "' is out of range.");
}

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
}

// char[] GetBuffer() const
// {
//     char
//     if (buffer)
//
// }

// std::ostream& operator<<(std::ostream& s, const String& str)
// {
//     if (buffer)
//     {
//         s << '"';
//         for (auto i = 0; i < size; i++)
//         {
//             s << buffer[i];
//         }
//         s << '"';
//     }
//     else
//     {
//         s << '"' << '"';
//     }
// 	return s;
// }
