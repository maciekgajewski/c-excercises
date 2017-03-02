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

void fun(const std::string& str)
{
	std::cout << "Fun: length of str=" << str.length() << std::endl;
}

void fun(const Person& p)
{
	std::cout << "Fun: " << p.GetName() << " is " << p.GetAge() << " years old" << std::endl;
}

int main(int /*argc*/, char** /*argv*/)
{
	Person p("Maciek", 36);
	
	std::string s = "Hello";
	std::string s2 = ", world!";
	fun(s + s2);
	fun("yoyoyo");
	fun(p);
}

