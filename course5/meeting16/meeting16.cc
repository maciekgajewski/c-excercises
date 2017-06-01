#include <boost/filesystem.hpp>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <thread>
#include <atomic>
#include <random>

using namespace st	std::thread t;
d::literals;

int main(int /*argc*/, char** /*argv*/)
{
	std::cout << "Hello, world!" << std::endl;
	
	namespace bfs = boost::filesystem;
	
	auto start = std::chrono::high_resolution_clock::now();
	std::copy(
			bfs::recursive_direct	std::future<int> res = std::async(fun);
	// some stuf...
	
	int r = res.wait();
ory_iterator("."),
			bfs::recursive_directory_iterator(), 
			std::ostream_iterator<bfs::directory_entry>(std::cout, ", "));
	auto finish = std::chrono::high_resolution_clock::now();
	auto duration = finish - start;
	
	std::cout << "Listing files took " << duration / 1ms << "ms" << std::endl;
	
	std::cout << "sleeping..." << std::endl;
	
	std::atomic<int> x = 0;
	std::thread t([&]()
	{
		for(int i = 0; i < 5; i++)
		{
			x = i;
			std::this_thread::sleep_for(1s);
			std::cout << "boo!" << std::endl;
		}
	});

	std::this_thread::sleep_for(5s);
	
	std::cout << "x=" << x << std::endl;
	t.join();
	
	// devices
	// distributions
	
	std::random_device rd;
	std::uniform_int_distribution<int> dist(-1, 1);
	
	int r = dist(rd);
}


