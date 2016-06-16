#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>


int main()
{
	std::vector<int> vec ;
	std::list<int> lst = {1, 3, 45, 6, 6, 6, 77};
	
	vec.reserve(lst.size());
	std::copy(lst.begin(), lst.end(), std::back_inserter(vec));
	
	std::sort(vec.begin(), vec.end());

	//for(int i : vec)
	//	std::cout << i << std::endl;
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, ", "));
}