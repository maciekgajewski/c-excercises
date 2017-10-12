#include <vector>
#include <iostream>
#include <string>

struct Data
{
	std::string name;
	Data(const std::string& n) : name(n) { std::cout << "Data(string)" << std::endl; }
	Data(const Data& c) : name(c.name) { std::cout << "Data copy" << std::endl; }
	Data(Data&& c) noexcept: name(std::move(c.name)) { std::cout << "Data move" << std::endl; }
	~Data() { std::cout << "~Data" << std::endl; }
};

int main(int argc, char** argv)
{
	std::vector<Data> v;
	v.push_back(Data{", world"});
	v.push_back(Data{"Hello"});
	std::cout << "v holds " << v.size() << " elements" << std::endl;

	for(int i = 0 ; i < v.size(); i++)
		std::cout << "v[" << i << "] = " << v[i].name << std::endl;
}

