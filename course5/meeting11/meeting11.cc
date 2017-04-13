#include <iostream>
#include <vector>

int main(int /*argc*/, char** /*argv*/)
{
	char arr[] = "Hello, world!";
	
	std::vector<char> chars(std::begin(arr), std::end(arr));
	for(char c : chars)
		std::cout << c;
	std::cout << std::endl;
}



