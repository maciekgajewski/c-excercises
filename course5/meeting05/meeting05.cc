#include <iostream>
#include <string>
#include <cassert>

struct Person
{
	Person() = delete;
	
	Person(std::string n, unsigned a)
		: name(n), age(a)
	{
	}

	std::string GetName() const { return name; }
	unsigned GetAge() const { return age; }
	
	void SetAge(unsigned a) { age = a; }
	
private:
	std::string name;
	unsigned age = 0;
};

std::ostream& operator<<(std::ostream& s, const Person& p)
{
	s << p.GetName() << " is " << p.GetAge() << " years old";
	return s;
}

int main(int /*argc*/, char** /*argv*/)
{
	Person p("Maciek", 36);
	std::cout << p << std::endl;
}

