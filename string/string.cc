#include "string.h"
#include <cstring>
#include <iostream>
#include <memory>

String::String()
{
    allocate(0);
    terminate();
}

String::~String()
{
}

String::String(const String &o)
{
    allocate(o.size());
    for (int i = 0; i < len; i++) DATA[i] = o.at(i);
    terminate();
}

String::String(String &&o)
{
    DATA = std::move(o.DATA);
    len = std::move(o.len);
}

String::String(const char *s)
{
    allocate(strlen(s));
    for (int i = 0; i < len; i++) DATA[i] = s[i];
    terminate();
}

String::String(const String &str, size_t pos, size_t len)
{
    if (pos > str.size())
    {
        String();
    }
    else
    {
        if (pos + len > str.size()) len = str.size() - pos;
        allocate(len);
        for (int i = 0; i < len; i++) DATA[i] = str.at(i + pos);
        terminate();
    }
}

String::String(const char *s, size_t n)
{
    len = strlen(s);
    if (len < n)
    {
        String(s);
    }
    else
    {
        allocate(n);
        for (int i = 0; i < n; i++) DATA[i] = s[i];
        terminate();
    }
}

String::String(size_t n, char c)
{
    allocate(n);
    for (int i = 0; i < n; i++) DATA[i] = c;
    terminate();
}

//template<typename It> String::String(It first, It last)
//{
//    // TODO: Not implemented yet
//}

std::size_t String::size() const
{
    return len;
}

bool String::empty() const
{
    // TODO: Not implemented yet
}

const char* String::c_str() const
{
    // TODO: Not implemented yet
}

char String::operator[](std::size_t pos) const
{
    // TODO: Not implemented yet
}

char& String::operator[](std::size_t pos)
{
    // TODO: Not implemented yet
}

String::iterator String::begin()
{
    // TODO: Not implemented yet
}

String::iterator String::end()
{
    // TODO: Not implemented yet
}

String::const_iterator String::begin() const
{
    // TODO: Not implemented yet
}

String::const_iterator String::end() const
{
    // TODO: Not implemented yet
}

void String::clear()
{
    // TODO: Not implemented yet
}

void String::swap(String& other)
{
    // TODO: Not implemented yet
}

String& String::operator = (const String& s)
{
    // TODO: Not implemented yet
}

String& String::operator = (const char* s)
{
    // TODO: Not implemented yet
}

String& String::operator = (String&& that)
{
    std::swap(DATA, that.DATA);
    return *this;
}

bool String::operator==(const String& s) const
{
    // TODO: Not implemented yet
}

bool String::operator==(const char* s) const
{
    // TODO: Not implemented yet
}

char String::at(size_t pos) const
{
    if (pos > len) throw std::out_of_range ("Argument is out of range");
    return DATA[pos];
}

void String::allocate(size_t len)
{
    if (len == 0)
    {
        this->len = 0;
        DATA = NULL;
    }
    else {
        this->len = len;
        DATA = std::unique_ptr<char[]>(new char[len + 1]);
    }
}

void String::terminate()
{
    if (len > 0) DATA[len] = '\0';
}

std::ostream& operator << (std::ostream & stream, const String &str)
{
    for (int i = 0; i < str.size(); i++) stream << str.DATA[i];
    return stream;
}
