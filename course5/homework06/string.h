#pragma once
#include <memory>
#include <ostream>
#include <cstdlib>


class String
{
public:
    String() = default;
    String(String &&);
    String(char* data);
    String(const char* data);
    String(const String& data);

    String& operator = (const String& string);
    String& operator = (String && string);
    String& operator = (const char* data);


    char& operator [](std::size_t index);
    const char& operator [] (std::size_t index) const;

    String& operator +=(const String& string);

    bool operator == (const String& s2) const;
    bool operator == (const char * str) const;

    const char * c_str() const;

    std::size_t length() const;
    std::size_t size() const;

    ~String();
private:
    void free();

    std::unique_ptr<char[]> buffer = nullptr;
};

String operator + (const String& s1, const String& s2);

std::ostream& operator << (std::ostream& stream, const String& string);
