#include "ustring.h"

#include <cstring>

namespace Course {

String::String(const char *str, size_t length)
{
    resize(length); // resize takes care of closing zero
    std::copy(str, str+length, data());
}

String::String(String &&rhs)
{
    mCapacity = rhs.mCapacity;
    mLength = rhs.mLength;
    mStr = std::move(rhs.mStr);
    rhs.mStr.emplace<SmallString>();
    rhs.mCapacity = SmallStringSize-1;
    rhs.mLength = 0;
    *(rhs.end()) = '\0';
}


String& String::operator=(const char *str)
{
    size_t length = std::strlen(str);
    resize(length);
    std::copy(str, str+length+1, data());
    return *this;
}

String& String::operator=(String const &rhs)
{
    resize(rhs.mLength);
    std::copy(rhs.cbegin(), rhs.cend()+1, data());
    return *this;
}

String& String::operator=(String &&rhs)
{
    if (this == &rhs) return *this;
    mCapacity = rhs.mCapacity;
    mLength = rhs.mLength;
    mStr = std::move(rhs.mStr);
    rhs.mStr.emplace<SmallString>();
    rhs.mCapacity = SmallStringSize-1;
    rhs.mLength = 0;
    *(rhs.end()) = '\0';
    return *this;
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
    if (size < SmallStringSize)
    {
        if (mCapacity == SmallStringSize-1) return;
        auto p = std::get_if<1>(&mStr);
        assert(p);
        std::unique_ptr<char[]> tmp = std::move(*p);
        mStr.emplace<SmallString>();
        std::copy(tmp.get(), tmp.get()+size, std::get<0>(mStr).str);
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
