#include <iostream>
#include <vector>
#include <cassert>
#include <list>

// template<typename T>
// void foo(std::vector<T>& vec)
// {
// 	assert(!vec.empty()); // better than vec.size() != 0
// 	auto first = vec.begin(); //std::vector<T>::iterator
// 	std::cout << *first << std::endl;
// 	vec.push_back(get_another<T>());
// 	std::cout << *first << std::endl;
// }

int main(int argc, char** argv)
{
	std::vector<std::string> s(argv, argv+argc);
	std::cout << "size=" << s.size() << ", capacity=" << s.capacity() << std::endl;
	
	std::list<std::string> l(s.rbegin(), s.rend());
	
	s.insert(s.end(), {"aa", "bb"});
	
	for(const std::string& str : s)
	{
		std::cout << str << std::endl;
	}
}

