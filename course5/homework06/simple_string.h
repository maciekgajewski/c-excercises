#pragma once
#include <iostream>
#include <memory>
#include <string>

namespace simple_string
{

class String
{
public:
    String();
    String(const char*);
    String(const String& src);
    String(String&& src);
    String& operator=(const String& src);
    String& operator=(String&& src);
    String& operator=(const char * src);
    String operator+(const char * src);
    String operator+(const String& src);
    String& operator+=(const char * src);
    String& operator+=(const String& src);

    char operator[](const int) const;
    char& operator[](const int);

    void Print() const;
    int Length() const;
    std::unique_ptr<char[]> GetBufferCpy() const;
    const char *CStr() const;

private:
    std::unique_ptr<char[]> buffer = nullptr;
    int size = 0;

}; // String

} // namespace

std::ostream& operator<<(std::ostream&, const simple_string::String&);
