#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/tokenizer.hpp>

namespace po = boost::program_options;

template <typename TComparer>
struct ColumnComparer
{
    ColumnComparer(int colNumber, char separator, const TComparer& comparer)
                   :colNumber(colNumber), separator(separator), comparer(comparer)
    { }

    bool operator() (const std::string& s1, const std::string& s2)
    {
        return comparer(this->FindColumnValue(s1), this->FindColumnValue(s2));
    }

    std::string FindColumnValue(const std::string& s)
    {
        boost::tokenizer<boost::char_separator<char>> tokenizer {s, boost::char_separator<char>(this->separator)};
        auto i = 0;
        auto cur = tokenizer.begin();
        int ix = 1;
        for (;ix < this->colNumber && cur != tokenizer.end(); ++ix)
            ++cur;
        if (ix != this->colNumber)
            return std::string();
        return *cur;
    }

private:
    int colNumber;
    char separator;
    const TComparer& comparer;
};

struct BasicComparer
{
    bool operator() (const std::string& s1, const std::string& s2)
    {
        return std::strcmp(s1.c_str(), s2.c_str()) < 0;
    }
};

struct NumericComparer
{
    bool operator() (std::string s1, std::string s2)
    {
        auto d1 = std::stod(s1);
        auto d2 = std::stod(s2);
        return d1 < d2;
    }
};


void CreateComparer(bool reverse, bool numeric, int columnIndex, char fieldSeparator)
{

}

po::variables_map vm;

po::options_description DeclareOptions()
{
    po::options_description desc;
    desc.add_options()
            ("help", "produce help message")
            ("reverse,r", "reverse the result of comparisons")
            ("numeric-sort,d", "compare according to string numerical value")
            ("key,c", po::value<int>(), "sort via a key; KEYDEF gives location and type")
            ("field-separator,s", po::value<char>(), "use SEP instead of non-blank to blank transition")
            ("input,i", po::value<std::string>(), "input file, default stdin")
            ("output,o", po::value<std::string>(), "output file, default stdout");
    return desc;
}

po::variables_map ReadOptions(int argc, char** argv, const po::options_description& desc)
{
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    return vm;
}

int main(int argc, char** argv)
{
    auto optionsDecl = DeclareOptions();
    auto options = ReadOptions(argc, argv, optionsDecl);

    if (options.count("help"))
    {
        std::cout << optionsDecl << std::endl;
        return 1;
    }



	return 0;
}
