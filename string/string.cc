#include "string.h"
#include <cstring>
#include <iostream>
#include <memory>
#include <algorithm>

String::String()
{
}

String::~String()
{
}

String::String(const String &o)
{
    allocate(o.size());
    std::copy(o.begin(), o.end() + 1, begin());
}

String::String(String &&o)
{
    mData = std::move(o.mData);
    mSize = std::move(o.mSize);
}

String::String(const char *s)
{
    allocate(strlen(s));
    std::strcpy(mData.get(), s);
    terminate();
}

String::String(const String &o, size_t pos, size_t len)
{
    if (pos <= o.size())
    {
        if (pos > o.size() - len)
        {
            len = o.size() - pos;
        }
        allocate(len);
        std::copy(o.begin() + pos, o.begin() + pos + len, begin());
        terminate();
    }
}

String::String(const char *s, size_t n)
{
    mSize = strlen(s);
    if (mSize < n)
    {
        String(s);
    }
    else
    {
        allocate(n);
        std::strncpy(mData.get(), s, n);
        terminate();
    }
}

String::String(size_t n, char c)
{
    allocate(n);
    for (int i = 0; i < n; i++) mData[i] = c;
    terminate();
}

template<typename It> String::String(It first, It last)
{
    std::size_t len = std::distance(first, last);
    allocate(len);
    std::copy(first, last, begin());
    terminate();
}

std::size_t String::size() const
{
    return mSize;
}

bool String::empty() const
{
    if (mSize == 0) {
        return true;
    } else {
        return false;
    }

}

const char* String::c_str() const
{
    if (mSize == 0)
    {
        return "\0";
    }
    else
    {
        return mData.get();
    }
}

char String::operator[](std::size_t pos) const
{
    return mData[pos];
}

char& String::operator[](std::size_t pos)
{
    // TODO: Not implemented yet
}

String::iterator String::begin()
{
    return mData.get();
}

String::iterator String::end()
{
    return mData.get() + size();
}

String::const_iterator String::begin() const
{
    return mData.get();
}

String::const_iterator String::end() const
{
    return mData.get() + size();
}

void String::clear()
{
    mData = nullptr;
    mSize = 0;
}

void String::swap(String& other)
{
    std::swap(mData, other.mData);
    std::swap(mSize, other.mSize);
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
    std::swap(mData, that.mData);
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
    if (pos > mSize) throw std::out_of_range ("Argument is out of range");
    return mData[pos];
}

void String::allocate(size_t len)
{
    if (len == 0)
    {
        mSize = 0;
        mData = nullptr;
    }
    else {
        mSize = len;
        mData = std::unique_ptr<char[]>(new char[len + 1]);
    }
}

void String::terminate()
{
    if (mSize > 0) mData[mSize] = '\0';
}

String operator +(const String& a, const String& b)
{
    String result;
    result.allocate(a.size() + b.size());
    std::copy(a.begin(), a.end(), result.begin());
    std::copy(b.begin(), b.end() + 1, result.begin() + a.size());

    return result;
}

std::ostream& operator << (std::ostream & stream, const String &str)
{
    for (int i = 0; i < str.size(); i++) stream << str.at(i);
    return stream;
}
