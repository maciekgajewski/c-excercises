#include "string.hh"
#include <cstring>
#include <memory>

namespace course {

string::string()
{
    clear();
}

string::string(const char * c)
{
    copyChars(c);
}

string::string(const string& source)
{
    copyChars(source.chars.get());
}

string::string(string&& source)
{
    stealChars(std::move(source));
}

bool string::empty() const
{
    return !mSize;
}

int string::size() const
{
    return mSize;
}

int string::length() const
{
    return mSize;
}

void string::clear()
{
    mSize = 0;
    chars = std::make_unique<char[]>(1);
    chars[0] = '\0';
}

const char * string::c_str() const
{
    return chars.get();
}

bool string::operator == (const string& other) const
{
    if(other.mSize != mSize)
    {
        return false;
    }

    for(int i=0; i< mSize; ++i)
    {
        if(chars[i]!= other.chars[i])
        {
            return false;
        }
    }

    return true;
}

bool string::operator != (const string& other) const
{
    return !(*this == other);
}

const char& string::operator [](const int index) const
{
    return chars[index];
}

char& string::operator [](const int index)
{
    return chars[index];
}

string string::operator + (const string& other) const
{
    string result(*this);
    result += other;
    return result;
}

string& string::operator =(const string& source)
{
   mSize = source.mSize;
   copyChars(source.chars.get());
}

string& string::operator =(string&& source)
{
   stealChars(std::move(source));
}

void string::stealChars(string&& source)
{
    mSize = source.mSize;
    chars = std::move(source.chars);
}

void string::copyChars(const char *c)
{
    mSize = std::strlen(c);
    chars = std::make_unique<char[]>(mSize+1);
    for(int i=0; i < mSize; ++i)
    {
        chars[i]= c[i];
    }

    chars[mSize] = '\0';
}

string& string::operator += (const string& other)
{
    int newSize = mSize + other.mSize;
    auto oldChars = std::move(chars);
    chars = std::make_unique<char[]>(newSize + 1);

    int i;
    for(i = 0; i< mSize; ++i)
    {
        chars[i] = oldChars[i];
    }

    for(i= mSize; i < newSize; ++i)
    {
        chars[i] = other[i - mSize];
    }

    chars[newSize] = '\0';

    mSize = newSize;
    return *this;
}
}
