#include "cpu.hh"

#include <boost/interprocess/managed_shared_memory.hpp>

#include <iostream>
#include <thread>
#include <atomic>
#include <array>
#include <future>

using namespace std::literals;
namespace bi = boost::interprocess;

const char* SHM = "course-shm";

int main(int argc, char** argv)
{
	std::cout << "start" << std::endl;
	int x = 0;

	std::future<int> res = std::async(std::launch::async, [&] 
	{
		for(int i = 0; i < 10; i++)
		{
			std::cout << "another thread: " << i << ", x=" << x << std::endl;
			std::this_thread::sleep_for(500ms);
		}
		return 66;
	});

		for(int i = 0; i < 5; i++)
		{
			std::cout << "main thread: " << i << std::endl;
			x = i;
			std::this_thread::sleep_for(500ms);
		}
	
	
	std::cout << "result = " << res.get() << std::endl;
	
	std::cout << "end" << std::endl;
}

