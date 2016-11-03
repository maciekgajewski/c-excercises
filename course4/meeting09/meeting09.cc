#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
	std::cout << "Hello, World!" << std::endl;
	
	std::vector<std::string> s(argv, argv+argc);
	std::cout << "size=" << s.size() << ", capacity=" << s.capacity() << std::endl;
	
	std::list<std::string> l(s.rbegin(), s.rend());
	
	for(const std::string& str : s)
	{
		std::cout << s << std::endl;
	}
	
// 	for(int i = 0; i < argc; i++)
// 	{
// 		//std::cout << s[i] << std::endl;
// 		std::cout << s.at(i) << std::endl;
// 	}
	
// 	s.reserve(argc);
// 	for(int i = 0; i < argc; i++)
// 	{
// 		s.push_back(argv[i]);
// 		std::cout << "size=" << s.size() << ", capacity=" << s.capacity() << std::endl;
// 	}
}

