#pragma once
#include <ostream>
#include <memory>

namespace course {
class string
{
public:
    string();
    ~string();
    string(const char* chars);
    string(const string& source);

    string& operator=(const string& source);
    bool operator ==(const string& a);
    bool operator ==(const char* chars);
    bool operator !=(const string& a) const;
    string& operator+=(const string& source);
    string operator+(const string& b) const;
    char& operator[](int index) const;

    const char* c_str() const;
    bool empty() const;
    int size() const;
    int length() const;
    void clear();

private:
    std::unique_ptr<char[]> mData;
    int mLength;
    int getLenghtOfChars(const char* chars);
    void deepCopy(const char* chars, int lenght);
    bool deepCompare(const char* chars, int length);
};

std::stringstream& operator <<(std::stringstream& os, const course::string &s);

}

