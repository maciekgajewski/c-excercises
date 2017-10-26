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

	std::vector<unsigned> buffer;
	buffer.resize(COUNT);
	random_file.read(reinterpret_cast<char*>(buffer.data()), sizeof(unsigned) * COUNT);

	std::list<unsigned> random_ints(buffer.begin(), buffer.end());

	// sort
	auto start = std::chrono::high_resolution_clock::now();
	random_ints.sort();
	auto end = std::chrono::high_resolution_clock::now();

	std::cout << COUNT << " numbers sorted in " << 0.001*(end-start)/1us << " ms" << std::endl;
	auto it = random_ints.begin();
	for(int i = 0; i < 20; i++, it++)
		std::cout << "#" << i << " : " << *it << std::endl;
}
 