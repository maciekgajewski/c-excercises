#include <boost/range/algorithm.hpp>

#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <memory>
#include <vector>


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

int main(int argc, char** argv)
{
    /*
    add params (help, file, asc/desc, field sep, col num, numeric)
    file-based
    */

	// std::sort(argv, argv+argc,
	// 	[](const char* a, const char* b)
	// 	{
	// 		return std::strcmp(a, b) < 0;
	// 	});
    //
	// for(int i = 0; i < argc; i++)
	// 	std::cout << argv[i] << std::endl;
    // std::cerr


    std::unique_ptr<std::vector<std::string>> buffer = std::make_unique<std::vector<std::string>>();
    std::string input;

    while ( std::getline(std::cin, input) )
    {
        buffer->push_back(input);
    }

    boost::sort(*buffer.get());

    for(auto item : *buffer.get())
		std::cout << item << std::endl;

}
