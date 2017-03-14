#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cassert>

#include "string.h"

using namespace jds;

void announce(char const * message);
void pass();

int main(int, char**)
{
	announce("ostream& operator<<");
	std::cout << "Testing with character string \"" << "abc" << "\"";
	pass();

	announce("default constructor");
	String empty;
	assert(std::strcmp(empty.c_str(), "") == 0);
	assert(empty.length() == 0);
	pass();

	announce("assignment from C string");
	String assigned_cstr = "abc";
	assert(std::strcmp(assigned_cstr.c_str(), "abc") == 0);
	assert(assigned_cstr.length() == 3);
	pass();

	announce("construction from C string");
	String constructed_cstr("abc");
	assert(std::strcmp(constructed_cstr.c_str(), "abc") == 0);
	assert(constructed_cstr.length() == 3);
	pass();

	announce("copy assignment");
	String assigned_copy;
	assigned_copy = constructed_cstr;
	assert(std::strcmp(assigned_copy.c_str(), "abc") == 0);
	assert(assigned_copy.length() == 3);
	pass();

	announce("copy construction");
	String constructed_copy = constructed_cstr;
	assert(std::strcmp(constructed_copy.c_str(), "abc") == 0);
	assert(constructed_copy.length() == 3);
	pass();

	announce("move assignment");
	String assigned_move;
	assigned_move = std::move(assigned_copy);
	assert(std::strcmp(assigned_move.c_str(), "abc") == 0);
	assert(assigned_move.length() == 3);
	assert(assigned_copy.length() == 0);
	pass();

	announce("move construction");
	String constructed_move = std::move(constructed_copy);
	assert(std::strcmp(constructed_move.c_str(), "abc") == 0);
	assert(constructed_move.length() == 3);
	assert(constructed_copy.length() == 0);
	pass();

	announce("operator[] const");
	String test_string = "abc";
	assert(test_string[0] == 'a');
	assert(test_string[1] == 'b');
	assert(test_string[2] == 'c');
	pass();

	announce("operator[] non-const");
	test_string[0] = 'd';
	test_string[1] = 'e';
	test_string[2] = 'f';
	assert(std::strcmp(test_string.c_str(), "def") == 0);
	pass();

	announce("operator+");
	assert(std::strcmp((assigned_cstr + test_string).c_str(), "abcdef") == 0);
	pass();

	announce("operator+=");
	assigned_cstr += test_string;
	assert(std::strcmp(assigned_cstr.c_str(), "abcdef") == 0);
	pass();

	return 0;
}

void announce(char const * message)
{
	std::cout << "Testing " << message << ": ";
}

void pass()
{
	std::cout << "passed" << std::endl;
}
