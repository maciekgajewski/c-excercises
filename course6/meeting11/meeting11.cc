#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <chrono>

using namespace std::literals;

int main(int argc, char** argv)
{
	// load 1M random numbers
	std::ifstream random_file("/dev/urandom");
	const std::size_t COUNT = 10000000;

	std::vector<unsigned int> random_ints;
	random_ints.resize(COUNT);
	random_file.read(reinterpret_cast<char*>(random_ints.data()), sizeof(unsigned int) * COUNT);

	// sort
	auto start = std::chrono::high_resolution_clock::now();

	std::sort(random_ints.begin(), random_ints.end());

	auto end = std::chrono::high_resolution_clock::now();

	std::cout << COUNT << " numbers sorted in " << (end-start)/1ms << " ms" << std::endl;

	auto it = random_ints.begin();
	for(int i = 0; i < 20; i++, it++)
		std::cout << "#" << i << " : " << *it << std::endl;
}
 