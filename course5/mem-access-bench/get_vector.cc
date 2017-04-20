#include <vector>
#include <stdexcept>
#include <algorithm>
#include <unordered_map>

std::vector<int> get_seq_vector(int size)
{
	std::vector<int> v;
	v.resize(size);
	for(int i =0 ; i < size; i++)
		v[i] = (i+1)%size;
	
	return v;
}

std::vector<int> get_random_vector(int size)
{
	std::vector<int> visit_order;
	visit_order.resize(size);
	for(std::size_t i =0 ; i < size; i++)
		visit_order[i] = i;
	
	std::random_shuffle(visit_order.begin()+1, visit_order.end());
	
	std::vector<int> vec;
	vec.resize(size);
	
	std::unordered_map<int, std::size_t> val2index;
	for(std::size_t i =0 ; i < size; i++)
		val2index.insert({visit_order[i], i});
	
	std::size_t current = 0;
	for(std::size_t i = 1; i < visit_order.size(); i++)
	{
		std::size_t next_pos = val2index[i];
		vec[current] = next_pos;
		current = next_pos;
	}
	
	return vec;
}

