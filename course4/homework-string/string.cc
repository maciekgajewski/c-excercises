#include "string.hh"
#include <sstream>
#include <iostream>

namespace course {

string::string()
{
    mLength = 0;
}

string::string(const char* chars)
{
    mLength = getLenghtOfChars(chars);
    mCharArray = std::make_unique<char[]>(mLength);
    deepCopy(chars, mLength);
}

string::string(const string& source)
{
    mLength = source.size();
    mCharArray = std::make_unique<char[]>(mLength);
    deepCopy(source.mCharArray.get(), mLength);
}

char& string::operator[](int index) const
{
    return mCharArray[index];
}


string& string::operator=(const string& source)
{
    mLength = source.size();
    mCharArray = std::make_unique<char[]>(mLength);
    deepCopy(source.mCharArray.get(), mLength);

    return *this;
}

bool string::operator==(const string& a)
{
    if(mLength!=a.mLength)
        return false;

    return deepCompare(a.mCharArray.get(), mLength);
}

bool string::operator ==(const char* chars)
{
    int charsLength = getLenghtOfChars(chars);
    if(mLength != charsLength)
        return false;

    return deepCompare(chars, mLength);
}

bool string::operator!=(const string& a)
{
    return mCharArray.get() != a.mCharArray.get();
}

bool string::empty() const
{
    if(mCharArray==nullptr)
        return true;

    return false;
}

int string::size() const
{
    return mLength;
}

 int string::getLenghtOfChars(const char* chars)
 {
     int charsLength = 0;
     while(chars[charsLength] != '\0')
     {
        charsLength++;
     }
     return charsLength;
 }

 void string::deepCopy(const char* chars, int length)
 {
     for(int j=0;j<length;++j)
     {
         mCharArray[j] = chars[j];
     }
 }

 bool string::deepCompare(const char* chars, int length)
 {
     for(int j=0;j<length;++j)
     {
         if(mCharArray[j] != chars[j])
             return false;
     }

     return true;
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
