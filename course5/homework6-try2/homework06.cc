#include "mystr.h"
#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstring>

void test_operators();
void test_basics();

using namespace mystring;

template <typename T>
void test_basics()
{
	std::cout << "====== Testing basics ======" << std::endl;

	T empty("");
	T empty_too; 
	std::cout << "created empty string" << std::endl;
	assert(empty.length() == 0); 
	assert(empty == empty_too); 
	assert(empty == ""); 

	// 2 empties should also be able to be non-compared
	if (empty != empty_too)
		assert(false);
	std::cout << "creating full string with different operator" << std::endl;
	T str("Hello world");
	assert(str.length() == 11); 
	assert(str ==  "Hello world" && str != "Hello worl"); 

	std::cout << "Created empty string str='"<< empty << "' and full string str='" << str  << "'" << std::endl;

	T str2 = str; // copy constructor
	std::cout << "Created str2 from str= "<<  str2 << std::endl; 
	assert(str == str2);

	T str3;
	str3 = "Haleluja"; // copy assignment with char*

	std::cout << "str3 created and assigned by copy. SHould be Haleluja: "<<  str3 << std::endl; 
	assert(str3 == "Haleluja");

	str3 = str2; // copy assignment with T
	std::cout << "str3. should be back to str2 (Hello World): "<<  str3 << std::endl; 
	assert(str3== str2);
	
	// Try corner cases
	empty = ""; // empty
	T non_empty = "Non empty";
	empty = non_empty; // Test assign non empty to empty
	assert (empty == non_empty);

	empty =  ""; 
	T empty2 ; 
	empty2 = empty; // assign empty to empty 
	assert (empty2 == empty); 

	non_empty = "full";
	empty = non_empty; // assign non empty to empty
	assert(empty == non_empty); 

	std::cout << "~~~~~ Finished Testing basics " << std::endl;
}

template <typename T> 
void test_operators()
{
	char test_str[] = "The Quick Brown Fox Jumps Over The Lazy Dog"; 
	std::cout << "====== Testing operators ======" << std::endl;
	T str(test_str);
	T str2 = std::move(str);
	T str3 = "Test string";
	T empty; 

	std::cout << "Moved String " << str2 <<  ". Len = "<< str2.length() << std::endl;
	assert (str2 == test_str);

	// test move assignment
	empty = std::move(str3);
	assert (empty == "Test string");
	std::cout << "Now mv assigned. Former empty string is now " << empty << std::endl;

	std::cout << "Iterating over string: " ; 
	for (unsigned int i = 0; i < str2.length(); i++)
	{
		std::cout << str2[i];
	}
	std::cout << std::endl;
	
	std::cout << "Testing accessing index beyond range" << std::endl;
	try
	{
		// Try to access beyong length. Should throw an error
		char c = str2[str2.length() + 5];
		std::cout << std::endl << ">>>>> WARNING: apprently can read beyond string length: '"<< c << "'" << std::endl;
	}
	catch(std::runtime_error& e)
	{
		std::cout << "caught expected exception: " << e.what() << std::endl;
	}

	std::cout << "Testing [] operator const and non const" << std::endl;
	str2[0] = 'X';
	std::cout << "Reassigned 1st character. String is now " << str2 << std::endl;
	assert (str2[0] == 'X');
	
	const T x("Non Mutable"); 
	std::cout << "1st char of " << x << "= "<< x[0] << std::endl;
	assert(x[0] == 'N'); // Can read from a const String
	
	std::cout << "Testing Addition Assignment"  << std::endl; 
	T str5 = "Hello ";
	T str6 = "World!"; 
	std::cout << str5 << " + "<< str6 << " = " ; 
	str5 += str6;
	std::cout << str5 << std::endl; 
	assert (str5 == "Hello World!");

	std::cout << "Testing COntatenation. " ; 
	T str7 = "Hello";
	T str8 = " World Again !";
	std::cout << str7 + str8 << std::endl;
	std::cout << "~~~~~ Finished Testing operators" << std::endl;
}
	
int main()
{
	std::cout << "Start of tests for std::string"<< std::endl;
	test_basics<std::string>();
	test_operators<std::string>();
	std::cout << "End of tests" << std::endl;

	std::cout << "Start of tests for MyString"<< std::endl;
	test_basics<MyString>();
	test_operators<MyString>();
	std::cout << "End of tests" << std::endl;

}
