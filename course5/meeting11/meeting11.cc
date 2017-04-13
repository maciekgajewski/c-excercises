#include <iostream>
#include <vector>
#include <cassert>

#include <memory>

// type requirements

struct FixedInMemory
{
	FixedInMemory(const FixedInMemory&) = delete;
	FixedInMemory(FixedInMemory&&) = delete;
	
	int mNum;
};

int main(int /*argc*/, char** /*argv*/)
{
	std::vector<FixedInMemory> v1;
	
	FixedInMemory f{6};
	
	v1.emplace_back(8);
	
	std::vector<int> v;
	
	v.reserve(10);
	for(int i = 0; i < 12; i++)
	{
		std::cout << "data when size=" << v.size()
			<< " : " << v.data()
			<< ", capacity=" << v.capacity()
			<< std::endl;
		v.push_back(i);
	}
	
	v.shrink_to_fit();
	
	std::cout << "final size=" << v.size()
		<< ", capacity=" << v.capacity()
		<< ", data=" << v.data()
		<< std::endl;
	
}



