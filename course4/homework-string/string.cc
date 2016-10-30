#include "string.hh"
#
#include <cstring>
#include <sstream>
#include <iostream>

namespace course {

string::string()
{
    mLength = 0;
}

string::string(const char* chars)
{
    mLength = std::strlen(chars);
    mData = std::make_unique<char[]>(mLength+1);
    std::copy(chars,chars+mLength, mData.get());
}

string::string(const string& source)
{
    mLength = source.size();
    mData = std::make_unique<char[]>(mLength+1);
    std::copy(source.mData.get(),source.mData.get()+mLength, mData.get());
}


char& string::operator[](int index) const
{
    return mData[index];
}


string& string::operator=(const string& source)
{
    mLength = source.size();
    mData = std::make_unique<char[]>(mLength+1);
    std::copy(source.mData.get(),source.mData.get()+mLength, mData.get());

    return *this;
}

bool string::operator==(const string& a)
{
    if(mLength!=a.mLength)
        return false;

    return (std::strcmp(a.mData.get(), mData.get()) == 0);
}

bool string::operator ==(const char* chars)
{
    int charsLength = std::strlen(chars);
    if(mLength != charsLength)
        return false;

    return (std::strcmp(chars, mData.get()) == 0);
}

bool string::operator!=(const string& a) const
{
    return mData.get() != a.mData.get();
}

string& string::operator+=(const string& a)
{
    auto totaLength = mLength + a.mLength;
    auto temp = std::make_unique<char[]>(totaLength+1);
    std::copy(mData.get(),mData.get()+mLength, temp.get());

    for(int j=0;j<=a.mLength;++j)
    {
        temp[j+mLength] = a.mData[j];
    }

    mLength = totaLength;
    mData = nullptr;
    mData = std::move(temp);
    return *this;
}

string string::operator+(const string& a) const
{
    string result(*this);
    result+=a;
    return result;
}

bool string::empty() const
{
    if(mData==nullptr)
        return true;

    return false;
}

int string::size() const
{
    return mLength;
}

int string::length() const
{
    return this->size();
}

const char* string::c_str() const
{
    if(mData==nullptr)
        return "\0";

    return mData.get();
}

 void string::clear()
 {
     mData = nullptr;
     mLength = 0;
 }

 char* string::begin()
 {
     return mData.get();
 }

 char* string::end()
 {
     return mData.get() + mLength;
 }

string::~string()
{
}

 std::stringstream& operator <<(std::stringstream& ss, const course::string &s)
 {
     for(int j=0;j<s.size();++j)
     {
         ss<<s[j];
     }
     return ss;
 }
}
