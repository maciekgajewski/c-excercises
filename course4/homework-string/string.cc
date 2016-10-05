#include "string.hh"

namespace course {

string::string()
{
}

string::string(const char * c)
{
    int i = 0;
    while(c[i] != '\0') // I guess we are not supposed to use strlen
    {
        chars.push_back(c[i]);
        ++i;
    }
}

string::string(const string& source)
{
    chars = source.chars;
}

string::string(string&& source)
{
    chars = std::move(source.chars);
}

bool string::empty() const
{
    return chars.empty();
}

int string::size() const
{
    return chars.size();
}

bool string::operator == (const string& other) const
{
    if(other.chars.size() != chars.size())
    {
        return false;
    }

    for(int i=0; i< chars.size(); ++i)
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
    chars = source.chars;
}

string& string::operator =(string&& source)
{
    chars = std::move(source.chars);
}
}
