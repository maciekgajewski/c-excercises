#include <iostream>
#include <unordered_map>
#include <string>

using namespace std::literals;

int main(int /*argc*/, char** /*argv*/)
{
	std::unordered_map<std::string, std::string> settings;
	
	settings["Greeting"] = "Hello";
	settings["Target"] = "World";
	
	std::cout << settings["Greeting"] << ", " << settings["Target"] << "!" << std::endl;
}
