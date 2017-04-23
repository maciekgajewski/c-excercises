#include <boost/range/algorithm.hpp>
#include <boost/program_options.hpp>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <memory>
#include <vector>
#include <stdexcept>


/***
Homework

Please, write a program that sorts text files.
The program should be able to sort files with multiple columns/fields per line.
The field separator, column number and sort direction should be configurable
Extra: There should be an option to sort by numerical value rather than text (ie “7” goes before “12”)

The program should be familiar, unix-style utility:
- The configuration should be passed by command-line options, both short (-s) and long (--long). -- help should print documentation.
- Unless specified otherwise, the input should be consumed from stdin, and the output produced to stdout, so that the program can be used in shell pipelines
- Any diagnostic/error messages should be printed to stderr
Implementation requirements:
- Use std stream API (ostream istream, fstream) for IO
- Use Boost.ProgramOptions for handling the command-line parameters
***/

void read(std::istream& in, std::vector<std::string>& buffer)
{
    std::string line;
    while (std::getline(in, line))
    {
        buffer.push_back(line);
    }
}

void write(std::ostream& out, std::vector<std::string>& buffer)
{
    for(auto item : buffer)
        out << item << std::endl;
}


int main(int argc, char** argv)
{
    namespace po = boost::program_options;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Show this message")
        ("input,i", po::value<std::string>(), "input file (defaults to stdin)")
        ("output,o", po::value<std::string>(), "output file (defaults to stdout)")
        ("desc,d", po::bool_switch(&flag), "description");
        // (help, file, asc/desc, field sep, col num, numeric)
    ;

    po::positional_options_description p;
    p.add("input", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;;
        return 1;
    }
    
    std::unique_ptr<std::vector<std::string>> buffer = std::make_unique<std::vector<std::string>>();
    if (vm.count("input"))
    {
        std::string in_fname = vm["input"].as<std::string>();
        std::ifstream infile(in_fname);
        if (infile)
        {
            read(infile, *buffer.get());
        }
        else
        {
            std::string msg = std::strerror(errno);
            throw std::runtime_error("Failed to open file: " + msg);
        }
    }
    else
    {
        read(std::cin, *buffer.get());
    }

    boost::sort(*buffer.get());

    if (vm.count("output"))
    {
        std::string out_fname = vm["output"].as<std::string>();
        std::ofstream outfile(out_fname);
        if (outfile)
        {
            write(outfile, *buffer.get());
        }
        else
        {
            std::string msg = std::strerror(errno);
            throw std::runtime_error("Failed to open file: " + msg);
        }
    }
    else 
    {
        write(std::cout, *buffer.get());
    }
}
