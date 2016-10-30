#include "string.hh"

#include <cassert>
#include <sstream>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

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

template<typename StringType>
void test2()
{
	StringType string1 = "12345678901234567890";
	StringType string2 = string1;
	
	assert(string2.length() == 20);
	
	// c_str test
	const StringType& cref = string1;
	assert(std::strlen(cref.c_str()) == 20);
	
	// operator +=
	string2 += string1;
	assert(std::strlen(string2.c_str()) == 40);
	
	// operator +
	StringType string3 = cref + string1;
	assert(std::strlen(string3.c_str()) == 40);
	
	assert(std::strcmp(string2.c_str(), string3.c_str()) == 0);
	assert(string2 == string3);
	assert(cref != string3);
	
	string1 = "abc";
	assert(std::strlen(cref.c_str()) == 3);
	assert(string2.length() == 40);
	
	string1 = "1234567890";
	assert(std::strlen(cref.c_str()) == 10);
	
	string1 = "zz";
	assert(std::strlen(cref.c_str()) == 2);

	string1 = "";
	assert(std::strlen(cref.c_str()) == 0);

	// clear
	string2.clear();
	assert(std::strlen(string2.c_str()) == 0);
	assert(string2.empty());
	assert(string2.length() == 0);
	
	// c_str on default - constructed
	StringType string4;
	assert(std::strlen(string4.c_str()) == 0);
	assert(string4.empty());
	assert(string4.length() == 0);
}

template<typename StringType>
void iteratorTest()
{
  //const iteration test
  const StringType s("ABCBB");
  int b_num = std::count_if(s.begin(), s.end(), [](const char& c){return c=='B';});
  assert(b_num == 3);

  // non-const test
  StringType s2("zaB1A2C3");
  std::sort(s2.begin(), s2.end());
  assert(s2=="123ABCaz");
}

int main()
{
	std::cout << "Testing std::string..." << std::endl;
	test<std::string>();
	test2<std::string>();
    iteratorTest<std::string>();
	std::cout << "std::string passes" << std::endl;

	std::cout << "Testing course::string..." << std::endl;
	test<course::string>();
	test2<course::string>();
    iteratorTest<course::string>();
	std::cout << "course::string passes" << std::endl;
}
