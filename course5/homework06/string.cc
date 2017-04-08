#include <cstring>
#include "string.h"

String::String(char * data)
    :String((const char *)data){}

String::String(const char *data)
{
    if (!data)
        throw std::runtime_error("expected non null char* data");
    std::size_t size = std::strlen(data) + 1;

    this->buffer = std::make_unique<char[]>(size);
    std::strcpy(this->buffer.get(), data);
}

String::String(const String & data)
    :String(data.buffer.get())
{}

String::String(String && data)
    :buffer(std::move(data.buffer))
{
    data.free();
}

std::size_t String::length() const
{
    if (buffer)
    {
        return std::strlen(this->buffer.get());
    }
    throw std::runtime_error("invalid state of an instance. buffer doesn't point to any meaningful value");
}

std::size_t String::size() const
{
    return this->length();
}

String::~String()
{
    this->free();
}

const char* String::c_str() const
{
    return this->buffer.get();
}

String& String::operator = (const String & string)
{
    this->free();
    size_t size = string.length();
    this->buffer = std::make_unique<char[]>(size);
    std::strcpy(this->buffer.get(), string.buffer.get());
    return *this;
}

String& String::operator =(String && string)
{    
    this->free();
    this->buffer = std::move(string.buffer);
    string.free();
    return *this;
}

bool String::operator ==(const String& str) const
{
    return strcmp(this->c_str(), str.c_str()) == 0;
}

bool String::operator ==(const char * str) const
{
    return strcmp(this->c_str(), str) == 0;
}

String operator +(const String& s1, const String& s2)
{
    auto size = s1.size() + s2.size();
    auto p = std::make_unique<char[]>(size);
    char* str = p.get();
    str = std::strcat(str, s1.c_str());
    str = std::strcat(str, s2.c_str());

    auto r = String(str);
    return r;
}

String& String::operator +=(const String& s)
{
    auto new_size = this->size() + s.size();
    auto new_buffer = std::make_unique<char[]>(new_size);

    strcat(new_buffer.get(), this->buffer.get());
    this->free();
    strcat(new_buffer.get(), s.c_str());
    this->buffer = std::move(new_buffer);
    return *this;
}

char& String::operator [](size_t index)
{
    return this->buffer.get()[index];
}

const char& String::operator [](size_t index) const
{
    return this->buffer.get()[index];
}


void String::free()
{
    if (this->buffer)
    {
        this->buffer.reset();
        this->buffer = nullptr;
    }
}
