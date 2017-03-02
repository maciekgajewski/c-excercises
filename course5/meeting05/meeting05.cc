#include <iostream>
#include <string>
#include <cassert>

class Counter
{
public:
	
	Counter(int& r) : mRef(r)
	{
	}
	
	Counter(const Counter& other) = delete;
	
	void Count()
	{
		mRef++;
	}
	
private:
	int& mRef;
};

int main(int /*argc*/, char** /*argv*/)
{
	int x = 0;
	Counter c1(x);
	Counter c2(x);
	
	c1.Count();
	c2.Count();
	c1.Count();
	
	//Counter c3; // if compiles: Counter has default constructor
	Counter c4 = c1; // if compiles - its copyable
	
	std::cout << "x = " << x << std::endl;
	
}

