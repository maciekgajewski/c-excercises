#include <iostream>
#include <string>
#include <vector>

class IPrintable
{
public:
	virtual void Print(std::ostream& o) const = 0;
};

class Person : public IPrintable
{
protected:
	std::string name;
	int age;

public:
	Person(const std::string& n, int a) : name(n), age(a) {}

	virtual void Print(std::ostream& o) const 
	{ o << name << " (aged " << age << ")"; }
};

class Employee : public Person
{
private:
	std::string role;
public:
	Employee(const std::string& n, int a, const std::string& r)
		: Person(n, a), role(r) {}

	void Print(std::ostream& o) const
	{ o << name << " the " << role << " (aged " << age << ")"; }
};

struct Triangle : public IPrintable
{
	Triangle(int xx, int yy, int zz) : x(xx), y(yy), z(zz) {}
	int x, y, z;
	void Print(std::ostream& o) const { o << "(" << x <<", " << y << ", " << z << " )"; }
};

std::ostream& operator<<(std::ostream& o, const IPrintable& p)
{
	p.Print(o);
	return o;
}

int main(int argc, char** argv)
{
	std::cout << "size of std::string: " << sizeof(std::string) << std::endl;
	std::cout << "size of Person: " << sizeof(Person) << std::endl;
	
	Employee maciek("Maciek", 37, "Teacher");
	Person misha("Misha", 31);
	Triangle t{1, 3, 6};

	std::vector<IPrintable*> printables;
	printables.push_back(&maciek);
	printables.push_back(&misha);
	printables.push_back(&t);
	
	for(IPrintable* p : printables)
		std::cout << "* " << *p << std::endl;
}
 