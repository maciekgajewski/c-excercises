#pragma once
#include <string>
#include <cstring>
#include <cstdio>
#include <stdexcept>
#include <boost/tokenizer.hpp>
#include <memory>

namespace homework12{

class AComparer
{
public:
    bool virtual operator() (const std::string& s1, const std::string& s2) const = 0;
};

std::unique_ptr<AComparer> CreateComparer(bool numeric, bool keyed, unsigned int column, char separator);

class BasicComparer : public AComparer
{
public:
    bool operator() (const std::string& s1, const std::string& s2) const override
    {
        return std::strcmp(s1.c_str(), s2.c_str()) < 0;
    }
};

class NumericComparer : public AComparer
{
public:
    bool operator() (const std::string& s1, const std::string& s2) const override
    {
        try
        {
            auto d1 = std::stod(s1);
            auto d2 = std::stod(s2);
            return d1 < d2;
        }
        catch(std::invalid_argument&)
        {
            return std::strcmp(s1.c_str(), s2.c_str()) < 0;
        }
    }
};
template <typename TComparer>
struct ColumnComparer: public AComparer
{
public:
    ColumnComparer(int colNumber, char separator)
                   :colNumber(colNumber), separator(separator), comparer(TComparer())
    {
        if (this->colNumber <= 0)
            throw std::invalid_argument("colNumber");
    }

    bool operator() (const std::string& s1, const std::string& s2) const override
    {
        const std::string c1 = this->FindColumnValue(s1);
        const std::string c2 = this->FindColumnValue(s2);
        return this->comparer(c1,c2);
    }

private:
    const std::string FindColumnValue(const std::string& s) const
    {
        const char * separators = {&this->separator};
        boost::char_separator<char> sep {separators};
        boost::tokenizer<boost::char_separator<char>> tokenizer {s, sep};
        auto cur = tokenizer.begin();
        int ix = 1;
        for (;ix < this->colNumber && cur != tokenizer.end(); ++ix)
            ++cur;
        if (cur == tokenizer.end())
            return std::string();
        return *cur;
    }

    int colNumber;
    char separator;
    const TComparer comparer;
};

}
