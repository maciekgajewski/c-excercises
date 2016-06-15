#pragma once

#include <memory>

class MyString
{
public:

    MyString();
    MyString(const char* inchar);
    MyString(const std::size_t size);
    MyString(const MyString&);

    std::size_t size() const;
    bool empty() const;
    const char* c_str() const;

    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;
    char& operator[](const std::size_t i) const;

    void operator=(const char* inchar);
    MyString& operator=(const MyString& other);
    MyString operator+(const MyString& other) const;
    MyString& operator+=(const MyString& other);

private:
    std::size_t mSize;
    std::unique_ptr<char[]> mBuffer;
};
