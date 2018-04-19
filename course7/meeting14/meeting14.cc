#include <iostream>
#include <string>

struct Person
{
	std::string name;
	double height;
};

std::ostream& operator<<(std::ostream& s, const Person& p)
{
	s << "Person{name: " << p.name << ", height: " << p.height << "cm}";
}

int main(int argc, char** argv)
{
	Person maciek { "Maciek", 2.00 };
	std::cout << maciek << std::endl;
}


