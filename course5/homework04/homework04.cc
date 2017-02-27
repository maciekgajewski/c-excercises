#include "Stream.h"
#include <cstdio>
#include <iostream>
#include <string>

//Stream Cout = Stream(std::cout);
Stream Cout = Stream(stdout);

int main()
{
	
	// Test catching
	try
	{
		Stream s("./non-existent/output.txt");
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught internal program error: " << e.what();
		std::cout << "continuing for now... " << std::endl;
		//std::exit(0);
	}

	try
	{
		std::cout << "Testing Stream object to output file output.txt " << std::endl; 
		Stream s("output.txt");
		std::string w = "World!"; 
		s << "Hello, " << w; 
		std::cout << "done" << std::endl; 

		std::cout << "Testing Cout" << std::endl; 
		Cout << "2 + 2 = "<< 2 + 2 << "\n"; 
		std::cout << "done" << std::endl; 
	
		std::cout << "Testing Stream object with flush() to output file file.txt " << std::endl; 
		Stream f("file.txt");
		f << "hey" << Endl;
		std::quick_exit(0);
		
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught internal program error: " << e.what() << std::endl;
	}

}
