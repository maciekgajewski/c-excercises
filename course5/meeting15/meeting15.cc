#include <iostream>
#include <stdexcept>

struct Cls
{
	Cls(int i) : id(i) {}
	~Cls() { std::cout << "Cls id=" << id << " destroyed" << std::endl; }
	
	int id;
};

int fun()
{
	Cls x(8);
	std::cout << "I'm in a fun" << std::endl;
	//throw new std::runtime_error("Hello, world!");
	//throw 77;
	return ERR;
	
}

int intermediate()
{
	Cls i(22);
	
	
	int r = fun();
	if(r != 0)
	{
		std::cout << "Logic error in fun: " << e.what() << std::endl;
		return r;
	}
	r = fun2();
	// TODO check...
	r = fun3();
	// TODO check 
	return r;
}

{
	fun();
	try { fun2(); } catch(...) { planBforFun2(); }
	fun3();
}

int main(int /*argc*/, char** /*argv*/)
{
	Cls top(0);
	try
	{
		Cls inTry(1);
		intermediate();
		std::cout << "Hello again!" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	catch(const std::runtime_error& e)
	{
		std::cout << "Runtime error: " << e.what() << std::endl;
	}
	catch(...)
	{
		Cls inCatch(5);
		std::cout << "Something's wrong..." << std::endl;
	}
	intermediate();
}


void c()
{
	T a;
	T b;
}

void a()
{
	a = new T;
	b = new T;
}

void d()
{
	auto a = std::make_unique<T>():
	auto b = std::make_unique<T>():
}


template<typename T>
class List
{
private:
	std::uniquye_ptr<Node<T>> mFirst;
	
public:
	
	void push_front(const T& v)
	{
		// bad
		auto rest = std::move(mFirst);
		mFirst = std::make_unique<Node<T>>(v);
		mFirst->next = std::move(rest);
		// good
		auto newFront = std::make_unique<Node<T>>(v);
		newFront->next = std::move(mFront);
		mFront = std::move(newFront);
	}
	
};

int div(double a, double b, double* result)
{
	if (b == 0)
			// what now?
	return a / b;
}


