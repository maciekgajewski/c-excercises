#include <iostream>
#include <unordered_map>
#include <string>

#include <set>

using namespace std::literals;

struct Person

{
	std::string name;
	int age;
	
	bool operator < (const Person& p2) const
	{
		return this->age < p2.age;
	}
	bool operator > (const Person& p2) const
	{
		return this->age > p2.age;
	}
};

std::ostream& operator<<(std::ostream& s, const Person& p)
{
	return s << "{" << p.name << ", aged " << p.age << "}";
}

struct ByName
{
	bool operator() (const Person& a, const Person& b) const
	{
		return a.name < b.name;
	}
};

int main(int /*argc*/, char** /*argv*/)
{
	std::multiset<Person, ByName> ppl;
	
	ppl.insert({"Maciek", 37});
	ppl.insert({"Alosha", 28});
	ppl.insert({"Jens", 33});
	ppl.insert({"Daniel", 28});
	
	for(auto& person : ppl)
		std::cout << person << std::endl;
}
