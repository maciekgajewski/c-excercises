#include <iostream>
#include <string>
#include <map>
#include <unordered_map>

int main(int argc, char** argv)
{
	std::multimap<std::string, int> map;

	//std::pair<int, std::string> 

	for (int i = 0; i < 10; i++)
	{
		//std::cout << "size: " << map.size() << ", buckets: " << map.bucket_count() << std::endl;
		map.insert(std::make_pair(std::to_string(i), i));
		//map[std::to_string(i)] =  i;
	}

	if (argc > 1)
	{
		std::string key = argv[1];
		int value = 666;

		auto result = map.insert({key, value});
		// if (result.second)
		// 	std::cout << "Inserted!" << std::endl;
		// else
		// 	std::cout << "Failed to insert, blocked by " << result.first->first << "->" << result.first->second << std::endl;

	}

	for(const auto& kv : map)
	{
		std::cout << kv.first << " -> " << kv.second << std::endl;
	}

}


