#include "ustring.h"

#include <cstring>

namespace Course {

char String::emptyString[] = "";

String::String(const char *str)
    : mLength(strlen(str))
    , mCapacity(mLength)
    , mStr(std::make_unique<char[]>(mLength+1))
{
    std::copy(str, str+length()+1, data());
}

String::String(String const &rhs)
    : mLength(rhs.length())
    , mCapacity(mLength)
    , mStr(std::make_unique<char[]>(mLength+1))
{
    std::copy(rhs.cbegin(), rhs.cend()+1, data());
}

String::String(const char *str, size_t length)
    : mLength(length)
    , mCapacity(mLength)
    , mStr(std::make_unique<char[]>(mLength+1))
{
    std::copy(str, str+length, data());
    *(end()) = '\0';
}

String::String(String &&rhs)
    : mLength(rhs.mLength)
    , mCapacity(rhs.mCapacity)
    , mStr(std::move(rhs.mStr))
{
    rhs.mCapacity = 0;
    rhs.mLength = 0;
}


String& String::operator=(const char *str)
{
    String tmp(str);
    std::swap(*this, tmp);
    return *this;
}

String& String::operator=(String rhs)
{
    swap(*this, rhs);
    return *this;
}

void swap(String& lhs, String &rhs)
{
    using std::swap;

    std::swap(lhs.mCapacity, rhs.mCapacity);
    std::swap(lhs.mLength, rhs.mLength);
    std::swap(lhs.mStr, rhs.mStr);
}

void String::resize(std::size_t size)
{
    if (mCapacity <= size)
        buffer_resize(size+1);
    mLength = size;
    *end() = '\0';
}

void String::resize(std::size_t size, char c)
{
    size_t oldLength = mLength;
    resize(size);
    if (oldLength < mLength)
    {
        std::fill(begin()+oldLength, end(), c);
    }
}

void String::buffer_resize(std::size_t size)
{
    if (mCapacity == size-1) return;
    if (size == 0)
    {
        mCapacity = 0;
        mStr = nullptr;
        return;
    }
    mCapacity = size-1;
    // TODO: clever resize
    auto newStr = std::make_unique<char[]>(size);
    std::copy(cbegin(), cend()+1, newStr.get());
    mStr = std::move(newStr);
}

void String::push_back(char c)
{
    resize(length()+1);
    at(length()-1) = c;
}

String String::operator+(char c) const
{
    String s(*this);
    s += c;
    return s;
}

String String::operator+(const char *str) const
{
    String s(*this);
    s += str;
    return s;
}

String String::operator+(const String &str) const
{
    String s(*this);
    s += str;
    return s;
}

String& String::operator+=(const char *str)
{
    size_t prevLength = length();
    size_t len = strlen(str);
    resize(prevLength+len);
    std::copy(str, str+len, begin()+prevLength);
    return *this;
}

String& String::operator+=(const String &str)
{
    size_t prevLength = length();
    resize(prevLength+str.length());
    std::copy(str.cbegin(), str.cend(), begin()+prevLength);
    return *this;
}

String operator+(char c, const String &rhs)
{
    String str;
    str.resize(rhs.size()+1);
    str[0] = c;
    std::copy(rhs.cbegin(), rhs.cend(), str.begin()+1);
    return str;
}

String operator+(const char *cstr, const String &rhs)
{
    String str;
    size_t cstr_length = strlen(cstr);
    str.resize(rhs.size()+cstr_length);
    std::copy(cstr, cstr+cstr_length, str.begin());
    std::copy(rhs.cbegin(), rhs.cend(), str.begin()+cstr_length);
    return str;
}

String operator "" _S(const char *cstr)
{
    return String(cstr);
}

} // namespace Course

std::ostream& operator<<(std::ostream &os, const Course::String &str)
{
    os.write(str.data(), str.length());
    return os;
}
