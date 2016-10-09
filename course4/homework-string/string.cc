#include "string.hh"
#include <cstring>
#include <memory>

namespace course {

string::string()
{
    mSize = 0;
}

string::string(const char * c)
{
    mSize = std::strlen(c);
    copyChars(c);
}

string::string(const string& source)
{
    mSize = source.mSize;
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
    source.chars = nullptr;
}

void string::copyChars(const char *c)
{
    chars = std::make_unique<char[]>(mSize);
    for(int i=0; i < mSize; ++i)
    {
        chars[i]= c[i];
    }
}
}
