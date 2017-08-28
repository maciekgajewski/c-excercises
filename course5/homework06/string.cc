#include "string.h"
#include<memory>
#include<algorithm>
#include<cstring>

String::String()
{

}

String::String(const String& src)   //copy constructor
{
    size = src.length();
    charbuffer = std::make_unique<char[]>(size+1);
    //for (int i=0; i < size+1; ++i)
    //{
        //charbuffer[i] = src.charbuffer[i];
    //}
    //std::copy(&(src.charbuffer[0]), &(src.charbuffer[size+1]), &(charbuffer[0])); //because charbuffer is unique pointer, otherwise if it's a char*, I can just use charbuffer
    std::copy(src.charbuffer.get(), src.charbuffer.get()+size+1, charbuffer.get());
}

String& String::operator= (const String& src)  //copy assignment
{
    size = src.length();
    charbuffer = std::make_unique<char[]>(size+1);
    std::copy(src.charbuffer.get(), src.charbuffer.get()+size+1, charbuffer.get());
    return *this;
}

String::String(String&& src)   //move constructor
{
    size = src.size;
    charbuffer = std::move(src.charbuffer);
    src.size = 0;
}

String& String::operator= (String&& src)    //move assignment
{
    size = src.size;
    charbuffer = std::move(src.charbuffer);
    src.size = 0;
    return *this;
}

String::String(const char* src)     //converting constructor
{
    *this = src;
}

String& String::operator= (const char* src)     //converting assignment
{
    size = std::strlen(src);
    charbuffer = std::make_unique<char[]>(size+1);
    for (int i=0; i < size+1; ++i)
    {
        charbuffer[i] = src[i];
    }
    return *this;
}

int String::length() const
{
    return size;
}

char& String::operator[] (int i)  //non-const version
{
    return charbuffer[i];
}

const char& String::operator[] (int i) const   //const version
{
    return charbuffer[i];
}

String String::operator+ (const String& src) const
{
    String result;
    result.size = size + src.size;
    result.charbuffer = std::make_unique<char[]>(result.size+1);
    std::copy(charbuffer.get(), charbuffer.get()+size, result.charbuffer.get());
    std::copy(src.charbuffer.get(), src.charbuffer.get()+src.size+1, &(result.charbuffer[size]));
    return result;
}

String String::operator+ (const char* src) const
{
    String result;
    result.size = size + std::strlen(src);
    result.charbuffer = std::make_unique<char[]>(result.size+1);
    std::copy(charbuffer.get(), charbuffer.get()+size, result.charbuffer.get());
    std::copy(src, src+strlen(src)+1, &(result.charbuffer[size]));
    return result;
}

String& String::operator+= (const String& src)
{
    *this = *this + src;
    return *this;
}

String& String::operator+= (const char* src)
{
    *this = *this + src;
    return *this;
}

const char* String::c_str() const
{
    if (charbuffer==nullptr)
        return "";
    return charbuffer.get();
}

bool String::operator== (const String& src)
{
    return std::strcmp(this->c_str(), src.c_str()) == 0;
}

bool String::operator!= (const String& src)
{
    return std::strcmp(this->c_str(), src.c_str()) != 0;
}

bool String::operator== (const std::string& src)
{
    return std::strcmp(this->c_str(), src.c_str()) == 0;
}

bool String::operator!= (const std::string& src)
{
    return std::strcmp(this->c_str(), src.c_str()) != 0;
}

bool String::operator== (const char* src)
{
    return std::strcmp(this->c_str(), src) == 0;
}

bool String::operator!= (const char* src)
{
    return std::strcmp(this->c_str(), src) != 0;
}

std::ostream& operator<< (std::ostream& stream, const String& src)
{
    stream << src.c_str();
    return stream;
}
