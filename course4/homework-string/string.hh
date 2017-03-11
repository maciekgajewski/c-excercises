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
    bool operator !=(const string& a);
    char& operator[](int index) const;

    bool empty() const;
    int size() const;

private:
    std::unique_ptr<char[]> mCharArray;
    int mLength;
    int getLenghtOfChars(const char* chars);
    void deepCopy(const char* chars, int lenght);
    bool deepCompare(const char* chars, int length);
};

std::stringstream& operator <<(std::stringstream& os, const course::string &s);

}


