#include "comparers.h"
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <fstream>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/tokenizer.hpp>

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
}

std::vector<std::string> ReadLines(std::istream&  file)
{
    std::vector<std::string> lines;
    std::string line;
    while(!file.eof())
    {
        std::getline(file, line);
        lines.push_back(line);
    }

    return lines;
}

void WriteLines(std::ostream& stream, std::vector<std::string>& lines)
{
    for (auto it = lines.begin(); it != lines.end(); ++it)
    {
        stream << it->c_str() << std::endl;
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
    std::fstream tmp_in;
    std::istream * input = &std::cin;
    if (options.count("input"))
    {
        std::string fname = options["input"].as<std::string>();
        tmp_in.open(fname.c_str(), std::fstream::in);
        if (!tmp_in.is_open())
        {
            std::cerr << "cannot open input file " + fname;
            std::cerr << std::endl;
            return 1;
        }
        input = &tmp_in;
    }

    std::ostream* output = &std::cout;
    std::ofstream tmp_out;
    if (options.count("output"))
    {
        tmp_out.open(options["output"].as<std::string>(), std::ofstream::out);
        if (!tmp_out.is_open())
        {
            std::cerr << "cannot open output file " + options["output"].as<std::string>();
            std::cerr << std::endl;
            return 1;
        }
        output = &tmp_out;
    }

    auto comparer = homework12::CreateComparer(numeric, keyed, colIndex, separator);

    auto lines = ReadLines(*input);
    std::sort(lines.begin(), lines.end(), [&comparer](std::string a, std::string b){return comparer->operator ()(a, b);});
    if (reverse)
        std::reverse(lines.begin(), lines.end());

    WriteLines(*output, lines);

	return 0;
}
