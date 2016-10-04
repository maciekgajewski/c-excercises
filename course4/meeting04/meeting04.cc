#include <iostream>
#include <memory>

struct Class
{
	// Default 
	Class() { std::cout << this << " Default constructed" << std::endl; }
	// Copy constructor
	Class(const Class& source) { std::cout << this << " Copied from " << &source << std::endl; }
	// Move constructor
	Class(Class&& source) { std::cout << this << " Moved from " << &source << std::endl; }
	
	// User-define
	explicit Class(const char* v) { std::cout << this << " Initialized with v=" << v << std::endl; }
	explicit Class(int a, int b) { std::cout << this << " Initialized with a=" << a << ", b=b" << std::endl; }
	// copy assignment
	Class& operator=(const Class& source) {
		std::cout << this << " Copy-assigned from " << &source << std::endl;
		return *this;
	}
	// move assignment
	Class& operator=(Class&& source) {
		std::cout << this << " Move-assigned from " << &source << std::endl;
		return *this;
	}
	
	~Class() { std::cout << this << " Destroyed" << std::endl; }
};


class UniquePtrClass
{
public:
	UniquePtrClass() : mPtr(nullptr) {}
	UniquePtrClass(Class* p) : mPtr(p) {}
	~UniquePtrClass() { delete mPtr; }
	UniquePtrClass(const UniquePtrClass&) = delete;
	UniquePtrClass(UniquePtrClass&& u)
	{
		mPtr = u.mPtr;
		u.mPtr = nullptr;
	}
	
	operator bool () const { return mPtr != nullptr; }
	
private:
	
	Class* mPtr;
};

UniquePtrClass MakeUniqueClass()
{
	return UniquePtrClass(new Class);
}

int main(int argc, char** argv)
{
	auto c = MakeUniqueClass();
	auto a = std::move(c);
	
	if (c)
	{
		std::cout << "up is not null" << std::endl;
	}
}

