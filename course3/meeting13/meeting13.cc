#include <stdexcept>
#include <iostream>
#include <string>

struct S
{
public:
	S(const std::string& name) : mName(name) {}
	~S() { std::cout << "Destroying " << mName << std::endl; }
private:
	std::string mName;
};

void fun(int argc) noexcept(true)
{
	S f1("f1");
	if (argc > 1)
		throw std::runtime_error("hello");
	S f2("f2");
}

int main(int argc, char** argv)
{
	try{
		S s("main");
		fun(argc);
		throw std::logic_error("7");
	}
	catch(const std::exception& e)
	{
		std::cout << "Exception : " << e.what() << std::endl;
		throw;
	}
}