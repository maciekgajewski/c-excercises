#include <cstdio>
#include <iostream>
#include <cassert>
#include <string>
#include <cstring>

void test_operators();
void test_basics();


void test_basics()
{
	std::cout << "====== Testing basics ======" << std::endl;
	std::string empty("");
	std::cout << "created empty std::string" << std::endl;
	assert(empty.length() == 0); 

	std::cout << "creating full std::string with different operator" << std::endl;
	std::string str("Hello world");
	assert(str.length() == 11); 

	std::cout << "Created empty std::string str='"<< empty << "' and full std::string str='" << str  << "'" << std::endl;

	std::string str2 = str; // copy constructor
	std::cout << "Created str2 from str= "<<  str2 << std::endl; 
	assert(str.length() == str2.length());

	std::string str3;
	str3 = "Haleluja"; // copy assignment with char*

	std::cout << "str3 created and assigned by copy. SHould be Haleluja: "<<  str3 << std::endl; 
	assert(str3.length() == std::strlen("Haleluja"));

	str3 = str2; // copy assignment with std::string
	std::cout << "str3. should be back to str2 (Hello World): "<<  str3 << std::endl; 
	assert(str3.length() == str2.length());
	

	std::cout << "~~~~~ Finished Testing basics " << std::endl;
}

void test_operators()
{
	char test_str[] = "The Quick Brown Fox Jumps Over The Lazy Dog"; 
	std::cout << "====== Testing operators ======" << std::endl;
	std::string str(test_str);
	std::string str2 = std::move(str);

	std::cout << "Moved String " << str2 <<  ". Len = "<< str2.length() << std::endl;
	assert (str2.length() == std::strlen(test_str));

	std::cout << "Iterating over std::string" ; 
	for (unsigned int i = 0; i < str2.length(); i++)
	{
		std::cout << str2[i];
	}
	std::cout << std::endl;
	
	std::cout << "Testing accessing index beyond range" << std::endl;
	try
	{
		// Try to access beyong length. Should throw an erro
		char c = str2[str2.length() + 1];
		std::cout << "ERROR: can read beyond std::string: "<< c << std::endl;
		assert (false);
	}
	catch(std::runtime_error& e)
	{
		std::cout << "caught expected exception: " << e.what() << std::endl;
	}

	std::cout << "Testing [] operator const and non const" << std::endl;
	str2[0] = 'X';
	std::cout << "Reassigned 1st character. String is now " << str2 << std::endl;
	assert (str2[0] == 'X');
	
	const std::string x("Non Mutable"); 
	std::cout << "1st char of " << x << "= "<< x[0] << std::endl;
	assert(x[0] == 'N'); // Can read from a const String
	
	std::cout << "Testing Addition Assignment"  << std::endl; 
	std::string str5 = "Hello ";
	std::string str6 = "World!"; 
	std::cout << str5 << " + "<< str6 << " = " ; 
	str5 += str6;
	std::cout << str5 << std::endl; 
	assert (str5.length() == 12);

	std::cout << "Testing COntatenation. " ; 
	std::string str7 = "Hello";
	std::string str8 = " World Again !";
	std::cout << str7 + str8 << std::endl;
	std::cout << "~~~~~ Finished Testing operators" << std::endl;
}
	
int main()
{
	std::cout << "Start of tests"<< std::endl;

	test_basics();
	test_operators();

	std::cout << "End of tests" << std::endl;
}
