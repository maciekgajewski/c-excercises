#include "simple_string.h"
#include <memory>
#include <stdexcept>
#include <cstring>


namespace simple_string
{

String::String() = default;

String::String(const char* initString)
{
    l = std::strlen(initString);
    buffer = std::make_unique<char[]>(l + 1);
    std::strcpy(buffer.get(), initString);
}

String::String(const String& src) // copy
{
    l = src.l;

    if (src.buffer)
    {
        buffer = std::make_unique<char[]>(l + 1);
        std::strcpy(buffer.get(), src.buffer.get());
    }
}

String::String(String&& src) // move
{
    buffer = std::move(src.buffer);
    l = src.l;

    src.buffer = nullptr;
    src.l = 0;
}

String& String::operator=(const String& src) // copy assignment
{
    l = src.l;
    if (src.buffer)
    {
        buffer = std::make_unique<char[]>(l + 1);
        std::strcpy(buffer.get(), src.buffer.get());
    }
    return *this;
}

String& String::operator=(String&& src) // move assignment
{
    buffer = std::move(src.buffer);
    l = src.l;

    src.buffer = nullptr;
    src.l = 0;

    return *this;
}

String& String::operator=(const char * src) // assignment from const char *
{
    l = std::strlen(src);
    buffer = std::make_unique<char[]>(l + 1);
    std::strcpy(buffer.get(), src);

    return *this;
}

String String::operator+(const char * src) // concatenation from const char *
{
    String s;
    int srcl = std::strlen(src);
    s.l = l + srcl;
    s.buffer = std::make_unique<char[]>(s.l + 1);
    for (auto i = 0; i < l; i++)
    {
        s.buffer[i] = buffer[i];
    }
    for (auto i = 0; i <= srcl; i++) // include null character
    {
        s.buffer[i + l] = src[i];
    }
    return s;
}

String String::operator+(const String& src) // concatenation from String
{
    String s;
    int srcl = src.l;
    s.l = l + srcl;
    s.buffer = std::make_unique<char[]>(s.l + 1);
    for (auto i = 0; i < l; i++)
    {
        s.buffer[i] = buffer[i];
    }
    for (auto i = 0; i <= srcl; i++) // include null character
    {
        s.buffer[i + l] = src.buffer[i];
    }
    return s;
}

String& String::operator+=(const char * src) // += from const char *
{
    int srcl = std::strlen(src);
    std::unique_ptr<char[]> newBuffer = std::make_unique<char[]>(l + srcl + 1);

    for (auto i = 0; i < l; i++)
    {
        newBuffer[i] = buffer[i];
    }
    for (auto i = 0; i <= srcl; i++) // include null character
    {
        newBuffer[i + l] = src[i];
    }
    l = l + srcl;
    buffer = std::move(newBuffer);
    return *this;
}

String& String::operator+=(const String& src) // += from String
{
    int srcl = src.l;
    std::unique_ptr<char[]> newBuffer = std::make_unique<char[]>(l + srcl + 1);

    for (auto i = 0; i < l; i++)
    {
        newBuffer[i] = buffer[i];
    }
    for (auto i = 0; i <= srcl; i++) // include null character
    {
        newBuffer[i + l] = src.buffer[i];
    }
    l = l + srcl;
    buffer = std::move(newBuffer);
    return *this;
}

bool String::operator==(const char * cmp) const
{
    int cmp_len = std::strlen(cmp);
    int max_len = std::max(l, cmp_len);
    return (std::strncmp(this->c_str(), cmp, max_len) == 0);
}

bool String::operator==(const String& cmp) const
{
    int cmp_len = cmp.l;
    int max_len = std::max(l, cmp_len);
    return (std::strncmp(this->c_str(), cmp.c_str(), max_len) == 0);
}

bool String::operator!=(const char * cmp) const
{
    int cmp_len = std::strlen(cmp);
    int max_len = std::max(l, cmp_len);
    return (std::strncmp(this->c_str(), cmp, max_len) != 0);
}

bool String::operator!=(const String& cmp) const
{
    int cmp_len = cmp.l;
    int max_len = std::max(l, cmp_len);
    return (std::strncmp(this->c_str(), cmp.c_str(), max_len) != 0);
}

char String::operator[](const int i) const
{
    if (buffer && i < l)
        return buffer[i];
    else
        throw std::range_error("Index error: '" + std::to_string(i) + "' is out of range.");
}

char& String::operator[](const int i)
{
    if (buffer && i < l)
        return buffer[i];
    else
        throw std::range_error("Index error: '" + std::to_string(i) + "' is out of range.");
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

int String::length() const
{
    return l;
}

const char *String::c_str() const
{
    const char *toReturn = "";
    if (buffer)
    {
        toReturn = buffer.get();
    }
    return toReturn;
}

std::ostream& operator<<(std::ostream& s, const String& str)
{
    s << str.c_str();
    return s;
}

bool operator==(const char * cmp, const String& cmp2)
{
    int cmp_len = std::strlen(cmp);
    int max_len = std::max(cmp2.length(), cmp_len);
    return (std::strncmp(cmp2.c_str(), cmp, max_len) == 0);
}
bool operator!=(const char * cmp, const String& cmp2)
{
    int cmp_len = std::strlen(cmp);
    int max_len = std::max(cmp2.length(), cmp_len);
    return (std::strncmp(cmp2.c_str(), cmp, max_len) != 0);
}
} // namespace
