#include "string.hh"

#include <cassert>
#include <sstream>
#include <iostream>
#include <string>

template<typename StringType>
void test()
{
	// Default construction
	StringType string1;
	
	// default created object is empty
	assert(string1.empty());
	assert(string1.size() == 0);
	
	// Initilized from string literal
	StringType string2("Hey");
	
	assert(!string2.empty());
	assert(string2.size() == 3);
	
	// Copy-construction
	StringType string3 = string2;
	
	assert(string2 == string3);
	assert(string3.size() == 3);
	
	// read-only character access
	
	assert(string3[0] == 'H');
	assert(string3[1] == 'e');
	assert(string3[2] == 'y');
	
	// writable character acess
	string2[2] = 'x';
	assert(string2 == "Hex");

	// copy is deep, so string3 remains unchanged
	assert(string3 == "Hey");
	assert(string2 != string3);

	// const-correctness test
	const StringType& string_const_ref = string3;
	assert(string_const_ref.empty() == false);
	assert(string_const_ref.size() == 3);
	assert(string_const_ref[0] == 'H');

	// Move construction
	StringType string4 = std::move(string3);
	assert(string4 == "Hey");

	// asignment operator
	string3 = string2;
	assert(string3 == "Hex");
	
	// writable character acess
	string2[2] = 'p';
	assert(string2 == "Hep");

	// copy is deep, so string3 remains unchanged
	assert(string3 == "Hex");
	assert(string2 != string3);
	
	// operator ostream<< tests
	std::stringstream ss;
	ss << string2 << string3;
	assert(ss.str() == "HepHex");
}


int main()
{
	std::cout << "Testing std::string..." << std::endl;
	test<std::string>();
	std::cout << "std::string passes" << std::endl;

	std::cout << "Testing course::string..." << std::endl;
	test<course::string>();
	std::cout << "course::string passes" << std::endl;
	
}