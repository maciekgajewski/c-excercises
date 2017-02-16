#include <iostream>
#include <string>

struct Vector
{
	std::int32_t x;
	std::int32_t y;
};

int main(int argc, char** argv)
{
	std::string h = "Hello, worl";
	std::string w = "d!";
	
	
	for(int i =0 ; i < 5; i++)
	{
		std::string s = std::to_string(i);
	}
	

	if(w == "d!")
	{
		std::string x = "X";
	}
	
	std::cout << h << w << std::endl;
	std::cout << "The size of std::string is: " << sizeof(std::string) << std::endl;
}
