#include <iostream>
#include <string>
#include <vector>

struct Fred
{
	Fred() { std::cout << "Fred created, this=" << this << std::endl; }
	explicit Fred(const std::string& n) : name(n) { std::cout << "Fred created, this=" << this << " : " << name << std::endl; }

	Fred(const Fred& other) : name(other.name) { std::cout << "Fred copied, this=" << this << ", other=" << &other << " : " << other.name << std::endl; }
	Fred(Fred&& other) noexcept : name(other.name) { std::cout << "Fred moved, this=" << this << ", other=" << &other << " : " << other.name << std::endl; }

	~Fred() { std::cout << "Fred destroyed, this=" << this << " : " << name << std::endl; }

	std::string name = "Fred";
};


int main(int argc, char** argv)
{
	std::vector<Fred> freds;
	for (int i = 1; i < argc; i++)
		freds.push_back(Fred(argv[i]));
	
	std::cout << "Container contains " << freds.size() << " elements" << std::endl;

	for(const Fred& f : freds)
		std::cout << f.name << std::endl;
}


