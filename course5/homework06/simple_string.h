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
    bool operator==(const char * cmp) const;
    bool operator==(const String& cmp) const;
    bool operator!=(const char * cmp) const;
    bool operator!=(const String& cmp) const;

    char operator[](const int) const;
    char& operator[](const int);

    void Print() const;
    int length() const;
    const char *c_str() const;

    typedef char * iterator;
    typedef const char * const_iterator;
    iterator begin() { return &buffer.get()[0]; }
    iterator end() { return &buffer.get()[l]; }

private:
    std::unique_ptr<char[]> buffer;
    int l = 0;

}; // String

std::ostream& operator<<(std::ostream&, const String&);
bool operator==(const char * cmp, const String& cmp2);
bool operator!=(const char * cmp, const String& cmp2);

} // namespace
