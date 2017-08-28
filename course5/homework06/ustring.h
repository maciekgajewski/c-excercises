#pragma once

#include <iostream>
#include <variant>
#include <stdexcept>
#include <string_view>
#include <limits>
#include <memory>
#include <cassert>

namespace Course {

class String
{
public:
    static constexpr std::size_t npos = -1;

    String() = default;

    String(const char *str) { *this = str; }
    String(const char *str, size_t length);
    String(String const &str) { *this = str; }
    String(String &&rhs);

    String& operator=(const char *str);
    String& operator=(String const &rhs);
    String& operator=(String &&rhs);

    // Element access
    char& operator[](std::size_t pos) { return data()[pos]; }

    const char& operator[](std::size_t pos) const { return data()[pos]; }

    char& at(std::size_t pos)
    {
        if (pos >= mLength)
            throw std::out_of_range("String::at");
        return (*this)[pos];
    }

    const char& at(std::size_t pos) const
    {
        if (pos >= mLength)
            throw std::out_of_range("String::at");
        return (*this)[pos];
    }

    char& front() { return (*this)[0]; }
    const char& front() const { return (*this)[0];  }

    char& back() { return (*this)[mLength-1]; }
    const char& back() const { return (*this)[mLength-1]; }

    char* data()
    {
        auto p0 = std::get_if<0>(&mStr);
        if (p0) return p0->str;
        auto p1 = std::get_if<1>(&mStr);
        return p1->get();
    }

    const char* data() const
    {
        auto p0 = std::get_if<0>(&mStr);
        if (p0) return p0->str;
        auto p1 = std::get_if<1>(&mStr);
        return p1->get();
    }

    const char* c_str() const { return data(); }

    // XXX operator std::string_view() const noexcept;

    // Iterators
    char* begin() { return data(); }
    const char* cbegin() const { return data(); }
    char* end() { return data()+length(); }
    const char* cend() const { return data()+length(); }

    // Capacity
    bool empty() const { return mLength == 0; }
    std::size_t size() const { return mLength; }
    std::size_t length() const { return mLength; }
    std::size_t max_size() const { return std::numeric_limits<std::size_t>::max(); }
    void reserve(std::size_t size)
    {
        if (size < mCapacity) return;
        buffer_resize(size);
    }

    std::size_t capacity() { return mCapacity; }
    void shrink_to_fit()
    {
        buffer_resize(mLength+1);
    }

    // Operations
    void clear() { resize(0); }

    void push_back(char c);
    // XXX char pop_back();
    String operator+(char c) const;
    String operator+(const char *str) const;
    String operator+(const String &str) const;
    String& operator+=(char c) { push_back(c); return *this; }
    String& operator+=(const char *str);
    String& operator+=(const String &str);
    void resize(std::size_t size);
    void resize(std::size_t size, char c);

private:

    void buffer_resize(std::size_t size);

    static constexpr std::size_t SmallStringSize = 32;
    struct SmallString
    {
        SmallString() = default;
        SmallString(const char *s, std::size_t length)
        {
            assert(length < SmallStringSize);
            std::copy(s, s+length, str);
        }
        char str[SmallStringSize];
    };
    std::size_t mCapacity = SmallStringSize-1;
    std::size_t mLength = 0;
    std::variant<SmallString, std::unique_ptr<char[]>> mStr = SmallString();
};

String operator+(char c, const String &str);
String operator+(const char *cstr, const String &str);

String operator "" _S(const char *);

} // namespace

std::ostream& operator<<(std::ostream &os, const Course::String &str);
