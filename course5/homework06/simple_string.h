#pragma once
#include <iostream>
#include <memory>

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
    const char *CStr() const;

private:
    std::unique_ptr<char[]> buffer;
    int size = 0;

}; // String

std::ostream& operator<<(std::ostream&, const String&);

} // namespace
