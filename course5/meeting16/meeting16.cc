#include <boost/optional.hpp>

#include <iostream>
#include <string>
#include <cstring>


bool fun1(const char* a, const char* b) {  std::cout << "Strcmp" << std::endl; return std::strcmp(a, b) > 0;  }

bool fun2(const std::string& a, const std::string&  b) {  std::cout << "std::string" << std::endl;return a > b;}

enum TestType { S, C};

template<TestType>
bool fun(const char* a, const char* b);

template<>
bool fun<S>(const char* a, const char* b) { return fun2(a, b); }

template<>
bool fun<C>(const char* a, const char* b) { return fun1(a, b); }

struct CStrComp
{
	bool operator()(const char* a, const char* b) const { return fun1(a, b); }
};

struct StringComp
{
	bool operator()(const std::string& a, const std::string&  b) const { return fun2(a, b); }
};

void test1()
{
	const char* a = "aa";
	const char* b = "bb";
	
	// yabdaba
	bool r = fun1(a, b);
	assert(!r);
}

void test2()
{
	const char* a = "aa";
	const char* b = "bb";
	
	// yabdaba
	bool r = fun2(a, b);
	assert(!r);
}


template<typename Comp>
void test(Comp c)
{
	const char* a = "aa";
	const char* b = "bb";
	
	// yabdaba
	bool r = c(a, b);
	assert(!r);
}

template<TestType TT>
void test3()
{
	const char* a = "aa";
	const char* b = "bb";
	
	// yabdaba
	bool r = fun<TT>(a, b);
	assert(!r);
}

int main(int /*argc*/, char** /*argv*/)
{
	test1();
	test2();
	
	test(CStrComp{});
	test(StringComp{});
	
	test3<C>();
	test3<S>();
}

