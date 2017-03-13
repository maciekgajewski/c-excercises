#include "simple_string.h"
#include <memory>
#include <string>
#include <stdexcept>


using namespace simple_string;

String::String() = default;

String::String(const char* initString)
{
    size = std::strlen(initString);
    buffer = std::make_unique<char[]>(size + 1);
    std::strcpy(buffer.get(), initString);
}

String::String(const String& src) // copy
{
    size = src.size;

    if (src.buffer)
    {
        buffer = std::make_unique<char[]>(size + 1);
        std::strcpy(buffer.get(), src.buffer.get());
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
        buffer = std::make_unique<char[]>(size + 1);
        std::strcpy(buffer.get(), src.buffer.get());
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
    size = std::strlen(src);
    buffer = std::make_unique<char[]>(size + 1);
    std::strcpy(buffer.get(), src);

    return *this;
}

String String::operator+(const char * src) // concatenation from const char *
{
    String s;
    int srcsize = std::strlen(src);
    s.size = size + srcsize;
    s.buffer = std::make_unique<char[]>(s.size + 1);
    for (auto i = 0; i < size; i++)
    {
        s.buffer[i] = buffer[i];
    }
    for (auto i = 0; i <= srcsize; i++) // include null character
    {
        s.buffer[i + size] = src[i];
    }
    return s;
}

String String::operator+(const String& src) // concatenation from String
{
    String s;
    int srcsize = src.size;
    s.size = size + srcsize;
    s.buffer = std::make_unique<char[]>(s.size + 1);
    for (auto i = 0; i < size; i++)
    {
        s.buffer[i] = buffer[i];
    }
    for (auto i = 0; i <= srcsize; i++) // include null character
    {
        s.buffer[i + size] = src.buffer[i];
    }
    return s;
}

String& String::operator+=(const char * src) // concatenation from const char *
{
    int srcsize = std::strlen(src);
    std::unique_ptr<char[]> newBuffer = std::make_unique<char[]>(size + srcsize + 1);

    for (auto i = 0; i < size; i++)
    {
        newBuffer[i] = buffer[i];
    }
    for (auto i = 0; i <= srcsize; i++) // include null character
    {
        newBuffer[i + size] = src[i];
    }
    size = size + srcsize;
    buffer = std::move(newBuffer);
    return *this;
}

String& String::operator+=(const String& src) // concatenation from String
{
    int srcsize = src.size;
    std::unique_ptr<char[]> newBuffer = std::make_unique<char[]>(size + srcsize + 1);

    for (auto i = 0; i < size; i++)
    {
        newBuffer[i] = buffer[i];
    }
    for (auto i = 0; i <= srcsize; i++) // include null character
    {
        newBuffer[i + size] = src.buffer[i];
    }
    size = size + srcsize;
    buffer = std::move(newBuffer);
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
        std::cout << buffer.get();
        std::cout << '"';
        std::cout << std::endl;
    }
    else
    {
        std::cout << "\"\"" << std::endl;
    }
}

int String::Length() const
{
    return size;
}

// std::unique_ptr<char[]> String::GetBufferCpy() const
// {
//     std::unique_ptr<char[]> bufferCpy = nullptr;
//     if (buffer)
//         bufferCpy = std::make_unique<char[]>(size);
//         std::strcpy(bufferCpy.get(), buffer.get());
//     return bufferCpy;
//
// }

// const char *String::CStr() const
// {
//     char res [size + 1];
//     if (buffer)
//     {
//         for (auto i = 0; i < size; i++)
//         {
//             std::cout << "Adding " << buffer[i] << std::endl;
//             res[i] = buffer[i];
//         }
//     }
//     // res[size] = '\0';
//     std::cout << "Returning " << res << std::endl;
//     const char *toReturn = &res[0];
//     std::cout << "Returning " << toReturn << std::endl;
//     return toReturn;
// }

// std::ostream& operator<<(std::ostream& s, const String& str)
// {
//     s << '"';
//     std::unique_ptr<char[]> bufferCpy = str.GetBufferCpy();
//     if (bufferCpy)
//     {
//         for (auto i = 0; i < str.Length(); i++)
//         {
//             s << bufferCpy[i];
//         }
//     }
//         s << '"';
// 	return s;
// }
