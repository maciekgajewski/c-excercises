#include <vector>
#include <iostream>
#include <string>
#include <list>

struct Data
{
	std::string name;
	Data(const std::string& n) : name(n) { std::cout << "Data(" << n << ")" << std::endl; }
	Data(const Data& c) : name(c.name) { std::cout << "Data copy " << name << std::endl; }
	Data(Data&& c) noexcept: name(std::move(c.name)) { std::cout << "Data move " << name << std::endl; }
	~Data() { std::cout << "~Data " << name << std::endl; }
};

int main(int argc, char** argv)
{
	std::vector<Data> v;

	v.reserve(argc);
	for(int i = 0; i < argc; i++)
		v.push_back(Data(argv[i]));

	std::cout << "v holds " << v.size() << " elements" << std::endl;

	for(const Data& d : v)
		std::cout << d.name << std::endl;
}

