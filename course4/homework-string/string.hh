#pragma once
#include <ostream>
#include<vector>
#include <memory>
#include <iostream>

namespace course {

class string
{
private:
    static constexpr char * emptyArray = "\0";
    std::unique_ptr<char[]> chars;
    int mSize;
    void copyChars(const char * c);
    void stealChars(string&& source);

public:
    string();

    string(const char * c);

    string(const string& source);

    string(string&& source);

    bool empty() const;

    int size() const;

    int length() const;

    bool operator == (const string& other) const;

    bool operator != (const string& other) const;

    const char& operator [](const int index) const;

    char& operator [](const int index);

    string& operator =(const string& source);

    string& operator =(string&& source);

    string operator + (const string& other) const;

    string& operator += (const string& other);

    char * begin();

    char * end();

    char * begin() const;

    char * end() const;

    const char * c_str() const;

    void clear();

    friend std::ostream& operator<<(std::ostream& os, const string& s);
};

inline std::ostream& operator<<(std::ostream& os, const string& s)
{
    for(int i=0; i < s.size(); ++i)
    {
        os << s.chars[i];
    }

    return os;
}
}
