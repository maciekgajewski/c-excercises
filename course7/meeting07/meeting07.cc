#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <array>

struct Fred
{
	Fred() { std::cout << "Fred created, this=" << this << std::endl; }
	explicit Fred(const std::string& n) : name(n) { std::cout << "Fred created, this=" << this << " : " << name << std::endl; }

	Fred(const Fred& other) = delete;
	Fred(Fred&& other) = delete;

//	Fred(const Fred& other) : name(other.name) { std::cout << "Fred copied, this=" << this << ", other=" << &other << " : " << other.name << std::endl; }
	//Fred(Fred&& other) noexcept : name(std::move(other.name)) { std::cout << "Fred moved, this=" << this << ", other=" << &other << " : " << name << std::endl; }

	~Fred() { std::cout << "Fred destroyed, this=" << this << " : " << name << std::endl; }

	std::string name = "Fred";
};


int main(int argc, char** argv)
{
	std::list<Fred> freds;
	//freds.reserve(argc-1);
	for (int i = 1; i < argc; i++)
	{
		freds.emplace_back(argv[i]);
		//freds.push_back(Fred(argv[i]));
	}
	
	std::cout << "Container contains " << freds.size() << " elements" << std::endl;
	//std::cout << "Container's capacity is " << freds.capacity() << std::endl;

	for(const Fred& f : freds)
		std::cout << f.name << std::endl;

	//auto dow = std::make_array("mon", "tue", "wed");
	std::array<std::string, 3> dow({"mon", "tue", "wed"});

	for(const auto& d : dow)
		std::cout << d << std::endl;

}


