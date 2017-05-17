#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/tokenizer.hpp>
#include "comparers.h"

namespace po = boost::program_options;
namespace homework12{

po::variables_map vm;

po::options_description DeclareOptions()
{
    po::options_description desc;
    desc.add_options()
            ("help", "produce help message")
            ("reverse,r", "reverse the result of comparisons")
            ("numeric-sort,d", "compare according to string numerical value")
            ("key,c", po::value<unsigned int>(), "sort via a key; value specifies column number")
            ("field-separator,s", po::value<char>()->default_value('/n'), "use SEP instead of non-blank to blank transition")
            ("input,i", po::value<std::string>()->default_value(""), "input file, default stdin")
            ("output,o", po::value<std::string>()->default_value(""), "output file, default stdout");
    return desc;
}

po::variables_map ReadOptions(int argc, char** argv, const po::options_description& desc)
{
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    return vm;
}
}

int main(int argc, char** argv)
{

    auto optionsDecl = homework12::DeclareOptions();
    auto options = homework12::ReadOptions(argc, argv, optionsDecl);

    if (options.count("help"))
    {
        std::cout << optionsDecl << std::endl;
        return 1;
    }
    bool reverse = false;
    bool numeric = false;
    bool keyed = false;
    int colIndex = 0;
    char separator = '\n';

    if (options.count("reverse"))
    {
        reverse = true;
    }

    if (options.count("numeric-sort"))
    {
        numeric = true;
    }

    if (options.count("key"))
    {
        colIndex = options["key"].as<unsigned int>();
        keyed = true;
        separator = options["field-separator"].as<char>();
    }
    auto comparer = homework12::CreateComparer(numeric, keyes, colIndex, separator);



	return 0;
}
