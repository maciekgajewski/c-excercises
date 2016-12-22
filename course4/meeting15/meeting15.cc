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
		{
			std::lock_guard<std::mutex> l(mutex_);
			buffer_ = v;
		}
		cv_.notify_all();
	}
	
	T wait()
	{
		std::unique_lock<std::mutex> l(mutex_);
		cv_.wait(l);
		return buffer_;
	}
	
private:
	
	std::mutex mutex_;
	T buffer_;
	//int wrtie_Seq
	std::condition_variable cv_;
};

int main(int argc, char** argv)
{
	std::cout << "start" << std::endl;
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
		std::this_thread::sleep_for(500ms);
		c.set(i);
	}
	c.set(-1);
	
	t.join();
	
	std::cout << "end" << std::endl;
}

