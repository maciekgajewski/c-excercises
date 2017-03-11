#include <memory>
#include <cstring>
#include "string.h"

namespace course{

    string::string() : len(0) {}

    string::string(const char* src)
    {
        len = std::strlen(src);
        string_pointer = std::make_unique<char[]>(len +1);
        std::strcpy(string_pointer.get(), src);
    }

    string::string(const string& src)
    {
        len = src.length();
        string_pointer = std::make_unique<char[]>(len +1);
        std::strcpy(string_pointer.get(), src.string_pointer.get());
    }

    string::string(string&& src)
    {
        len = src.length();
        string_pointer = std::make_unique<char[]>(len +1);
        string_pointer = std::move(src.string_pointer);
    }


    int string::length() const {return len;}

    string& string::operator=(const string& src)
    {
        len = src.length();
        string_pointer = std::make_unique<char[]>(len +1);
        std::strcpy(string_pointer.get(), src.string_pointer.get());
        return *this;
    }

    string& string::operator=(const char* src)
    {
        len = std::strlen(src);
        string_pointer = std::make_unique<char[]>(len +1);
        std::strcpy(string_pointer.get(), src);
        return *this;
    }

    string& string::operator=(string&& src)
    {
        len = src.length();
        string_pointer = std::make_unique<char[]>(len +1);
        string_pointer = std::move(src.string_pointer);
        return *this;
    }

    bool string::operator==(const string& src)
    { 
        return !std::strcmp(string_pointer.get(), src.string_pointer.get());
    }

    bool string::operator==(const char* src)
    { 
        return !std::strcmp(string_pointer.get(), src);
    }

    string string::operator+(const string& src)
    {
        string result;
        result.len = len + src.length();
        result.string_pointer = std::make_unique<char[]>(result.len + 1);
        result[0] = '\0';
        std::strcat(result.string_pointer.get(), this->string_pointer.get());
        std::strcat(result.string_pointer.get(), src.string_pointer.get());
        return result;
    }

    string& string::operator+=(const string& src)
    {
        len += src.length();
        std::unique_ptr<char[]> new_string_pointer = std::make_unique<char[]>(len + 1);
        new_string_pointer.get()[0] =  '\0';
        std::strcat(new_string_pointer.get(), string_pointer.get());
        std::strcat(new_string_pointer.get(), src.string_pointer.get());
        string_pointer = std::make_unique<char[]>(len + 1);
        string_pointer = std::move(new_string_pointer);
        return *this;
    }

    char& string::operator[](const int i)
    {
        return string_pointer.get()[i];
    }

    char string::operator[](const int i) const
    {
        return string_pointer.get()[i];
    }

    char* string::c_str() const { return string_pointer.get(); }

    std::ostream& operator<<(std::ostream& stream, const string& s)
    {
        return stream << s.c_str();
    }

}