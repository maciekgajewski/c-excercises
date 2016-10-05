#pragma once
#include <ostream>
#include<vector>

namespace course {

class string
{
private:
	std::vector<char> chars;

public:
    string();

    string(const char * c);

    string(const string& source);

    string(string&& source);

    bool empty() const;

    int size() const;

    bool operator == (const string& other) const;

    bool operator != (const string& other) const;

    const char& operator [](const int index) const;

    char& operator [](const int index);

    string& operator =(const string& source);

    string& operator=(string&& source);

    friend std::ostream& operator<<(std::ostream& os, const string& s)
    {
        for(int i=0; i < s.chars.size(); ++i)
        {
            os << s.chars[i];
        }

        return os;
    }
};
}
