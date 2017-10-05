#include <iostream>
#include <string>

struct Record
{
	std::string name;
	int id;
	float factor;
};

int main(int argc, char** argv)
{
	Record datum;
	datum.name = "Hello";
	std::cout << datum.name << std::endl;
}

