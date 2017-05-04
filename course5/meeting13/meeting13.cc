#include <iostream>
#include <unordered_map>
#include <string>

#include <set>
#include <map>
#include <vector>
#include <algorithm>

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
	using Year = int;
	std::multimap<Year, Person> pplById;

	std::vector<std::pair<Year, Person>> ppl;
	
	std::pair<Year, Person> data[] = {
		{1980, {"Maciek", 37}},
		{1989, {"Alosha", 28}},
		{1989, {"Daniel", 28}},
		{1989, {"Balazs", 28}},
		{1984, {"Jens", 33}}
	};
	
	pplById.insert(std::begin(data), std::end(data));
	
	for(auto& p : pplById)
	{
		std::cout << p.first << " : " << p.second << std::endl;
	}
	
	if (argc > 2)
	{
		Year first = std::stoi(argv[1]);
		Year last = std::stoi(argv[2]);
		
		auto it_first = pplById.lower_bound(first);
		auto it_last = pplById.upper_bound(last);
		
		std::cout << "ppl born in " << first << " - " << last
			<< "(found: " << std::distance(it_first, it_last) << ")"
		<< std::endl;
		
		int num = 0;
		std::for_each(it_first, it_last, [&](auto& p)
		{
			std::cout << p.second << std::endl;
			num++;
		});
		std::cout << "(records: " << num << ")" << std::endl;
	}
}
