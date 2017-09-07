#include <iostream>
#include <string>

struct Vector
{
	double x = 0.0;
	double y = 0.0;
};

struct Person
{
	Person(std::string& n, int a)
	{
		name = n;
		age = a;
	}

	Person(const Person& other) = delete;
	Person& operator=(const Person&) = delete;

private:
	std::string name;
	int age;
};

std::string getName() { return "Thomas"; }

int main(int argc, char** argv)
{
	int x = 8;
	int y = x;

	std::string s = getName();
	s = getName();

	Vector v;
	Person p("Maciek", 37);
	Person p2("Adam", 27);
}

