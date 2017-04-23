#include <iostream>
#include <algorithm>
#include <cstring>


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
    using namespace std::literals;
    /*
    pipeable
    install Boost
        find_package(Boost REQUIRED)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
        set(CMAKE_CXX_STANDARD 14)
        include_directories(${Boost_INCLUDE_DIR})
    add params (help, file, asc/desc, field sep, col num, numeric)
    file-based
    */

	std::sort(argv, argv+argc,
		[](const char* a, const char* b)
		{
			return std::strcmp(a, b) < 0;
		});

	for(int i = 0; i < argc; i++)
		std::cout << argv[i] << std::endl;

}
