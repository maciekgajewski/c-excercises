#include <iostream>
#include <unordered_map>
#include <string>

#include <set>
#include <map>
#include <vector>

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

int main(int argc, char** argv)
{
	using ID = int;
	std::map<ID, Person> pplById;

	std::vector<std::pair<ID, Person>> ppl;
	
	ppl.push_back({1234, {"Maciek", 37}});
	ppl.push_back({1234, {"Alosha", 28}});
 	ppl.push_back({775554, {"Jens", 33}});
 	ppl.push_back(std::make_pair(34455, Person{"Daniel", 28}));
	
	for(auto& p : ppl)
	{
		auto result = pplById.insert(std::move(p));
		if (!result.second)
		{
			std::cout << "ERROR: duplicate id, person " << p.second.name << " has the same id as "
				<< result.first->second.name << ", the id is " << p.first << std::endl;
		}
	}
	
	for(auto& p : pplById)
	{
		std::cout << p.first << " : " << p.second << std::endl;
	}

	if (argc > 1)
	{
		ID id = std::stoi(argv[1]);
		std::cout << "Person with id " << id << " : " << pplById.at(id) << std::endl;
	}
}
