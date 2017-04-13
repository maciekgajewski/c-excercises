#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <list>
#include <deque>
#include <array>

#include <memory>

// type requirements

struct S
{
	S() = delete;
	
	S(S&& o)
		: mStr(std::move(o.mStr))
	{
		std::cout << "move ctor of obj with mStr=" << mStr << std::endl;
	}

	S(const std::string& s)
		: mStr("From string: " + s)
	{ }
	
	S(int i)
		: mStr("From int:" + std::to_string(i))
	{ }
		
	S& operator=(S&&) = default;
	
	std::string mStr;
};

int main(int /*argc*/, char** /*argv*/)
{
	std::deque<S> v1;
	//std::vector<S> v2(8); fails

	std::array<S, 6> a;
	
	v1.emplace_back(156);
	auto it = v1.begin();
	v1.emplace_back("wooo");
	std::cout << "it ponts to: " << it->mStr << std::endl;
	it = v1.begin();
	v1.erase(it);
	
	std::cout << "it ponts to: " << it->mStr << std::endl;
	
	for(auto& s : v1)
		std::cout << s.mStr << std::endl;
	
}



