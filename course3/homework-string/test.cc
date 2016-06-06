#include "my_string.h"

#include <string>
#include <cassert>
#include <iostream>
#include <cstring>

template<typename StringType>
void string_test()
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
	
	// writable charactetr acess
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

	// c_str test
	assert(std::strcmp(string_const_ref.c_str(), "Hey") == 0);

	// assignment operator test
	std::cout << "pre copy-assignment operator";
	string3 = "abc";
	assert(string_const_ref == "abc");
	
	string3 = string2;
	assert(string_const_ref == "Hex");
	assert(string2 == "Hex");
	
	/*


	// operator +
	StringType plusResult = string_const_ref + StringType("123");
	assert(plusResult == "Hex123");
        
	StringType plusResultEmpty = StringType() + StringType();
	assert(plusResultEmpty.empty());
	assert(plusResultEmpty.size() == 0); 
	
	StringType plusResult2 = StringType() + StringType("777");
	assert(plusResult2 == "777");
	
	StringType plusResult3 = StringType("888") + StringType();
	assert(plusResult3 == "888");

	// operator +=

	plusResult += "";
	assert(plusResult == "Hex123");

	plusResult += StringType();
	assert(plusResult == "Hex123");

	plusResult += string2;
	assert(plusResult == "Hex123Hex");

	StringType emptyPlus;
	emptyPlus += StringType();
	assert(emptyPlus.empty());
	assert(emptyPlus.size() == 0);
	
	// operator <
	assert(StringType() < StringType("0"));
	assert(StringType("0") < StringType("1"));
	assert(!(StringType("1") < StringType("0")));
	assert(!(StringType("1") < StringType()));
*/
}


int main()
{
	// pre-test - of this _doesn't_ crash your program, you faield to compile it in debug mode (g++ -g)
	// if it crashes, it's a good sign. Remove the line and proceed.
//	assert(false);
	
	// test fior std::string - works
	std::cout << "Testing std::string..." << std::endl;
	string_test<std::string>();
	std::cout << "std::string test passes" << std::endl;
	
	// test for your string - it should compile and pass pass
	std::cout << "Testing MyString..." << std::endl;
	string_test<MyString>();
	std::cout << "MyString test passes" << std::endl;
}
