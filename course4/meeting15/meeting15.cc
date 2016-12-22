#include "cpu.hh"

#include <boost/interprocess/managed_shared_memory.hpp>

#include <iostream>
#include <thread>
#include <atomic>
#include <array>
#include <future>
#include <condition_variable>
#include <mutex>

using namespace std::literals;
namespace bi = boost::interprocess;

const char* SHM = "course-shm";

template<typename T>
class communicator
{
public:
	
	void set(const T& v)
	{
		buffer_ = v;
		seq_++;
	}
	
	T wait()
	{
		int prev = seq_;
		while(prev == seq_)
			;
		
		return buffer_;
	}
	
private:
	std::atomic<int> seq_;
	T buffer_;
};
using comm = communicator<int>;
int main(int argc, char** argv)
{
	std::cout << "start" << std::endl;
	
	if (argc < 2)
	{
		std::cout << "usage PROG client|server" << std::endl;
		return 1;
	}
	
	
	if (argv[1] == "server"s)
	{
		bi::shared_memory_object::remove(SHM);
		bi::shared_memory_object shm(bi::create_only, SHM, bi::read_write);
		
		shm.truncate(sizeof(comm));
		
		bi::mapped_region region(shm, bi::read_write);
		
		void* addr = region.get_address();
		std::cout << "got shared memory at " << addr << std::endl;
		comm* c = new(addr) comm;
		
		for(int i = 0; i < 50; i++)
		{
			std::cout << "server: " << i << std::endl;
			std::this_thread::sleep_for(1s);
			c->set(i);
		}
		c->set(-1);

		
		c->~comm();
		
	}
	else
	{
		bi::shared_memory_object shm(bi::open_only, SHM, bi::read_write);
		bi::mapped_region region(shm, bi::read_write);
		
		void* addr = region.get_address();
		std::cout << "client got shared memory at " << addr << std::endl;
		comm* c = reinterpret_cast<comm*>(addr);
		
		while(true)
		{
			int v = c->wait();
			std::cout << "got: " << v << std::endl;
			if (v == -1)
				break;
		}

	}
	/*
	communicator<int> c;

	std::thread t([&] 
	{
		while(true)
		{
			int v = c.wait();
			std::cout << "got: " << v << std::endl;
			if (v == -1)
				break;
		}
	});

	for(int i = 0; i < 5; i++)
	{
		std::cout << "main thread: " << i << std::endl;
		std::this_thread::sleep_for(10us);
		c.set(i);
	}
	c.set(-1);
	
	t.join();
	
	*/
	std::cout << "end" << std::endl;
}

