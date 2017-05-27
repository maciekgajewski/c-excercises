#include "string.h"
#include <cstring>

String::String(const char *data)
{
    if (data)
    {
        std::size_t len = std::strlen(data);
        if (len > 0)
        {
            std::size_t size = len + 1;
            this->buffer = std::make_unique<char[]>(size);
            std::strcpy(this->buffer.get(), data);
        }
    }
}

String::String(const String & data)
    :String(data.buffer ? data.buffer.get() : nullptr)
{}

String::String(String && data)
{
    if (data.buffer != nullptr)
        buffer = std::move(data.buffer);
    data.buffer = nullptr;
}

std::size_t String::length() const
{
    if (this->buffer)
    {
        return std::strlen(this->buffer.get());
    }
    return 0;
}

std::size_t String::size() const
{
    return this->length();
}

const char* String::c_str() const
{
    if (this->buffer)
        return this->buffer.get();
    else return "";
}

String& String::operator = (const String & string)
{
    if (!string.buffer)
    {
        this->buffer = nullptr;
    }
    else
    {
        size_t size = string.length();
        this->buffer = std::make_unique<char[]>(size + 1);
        std::strcpy(this->buffer.get(), string.buffer.get());
    }
    return *this;
}

String& String::operator =(String && string)
{
    this->buffer = std::move(string.buffer);
    string.buffer = nullptr;
    return *this;
}

bool String::operator ==(const String& str) const
{
    return std::strcmp(this->c_str(), str.c_str()) == 0;
}

bool String::operator ==(const char * str) const
{
    return std::strcmp(this->c_str(), str) == 0;
}

bool String::operator !=(const String& str) const
{
    return !((*this) == str);
}

bool String::operator !=(const char* str) const
{
    return !((*this) == str);
}

String operator +(const String& s1, const String& s2)
{
    auto r = String(s1);
    r += s2;

    return r;
}

String& String::operator +=(const String& s)
{
    auto new_size = this->size() + s.size();
    auto new_buffer = std::make_unique<char[]>(new_size + 1);
    std::strcat(new_buffer.get(), this->c_str());
    std::strcat(new_buffer.get(), s.c_str());
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
