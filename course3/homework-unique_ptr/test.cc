#include "my_unique_ptr.h"

#include <iostream>
#include <cassert>

class TestClass
{
public:
	TestClass()
	{
		std::cout << "TestClass::ctor" << std::endl;
	}

	TestClass(const TestClass& that)
	{
		std::cout << "TestClass::Copy" << std::endl;
	}

	TestClass(const TestClass&& that)
	{
		std::cout << "TestClass::Move" << std::endl;
	}

	~TestClass()
	{
		std::cout << "TestClass::Destruct" << std::endl;
	}
};

int main()
{
	MyUniquePtr<TestClass> testptr;
	assert(testptr == nullptr);

	MyUniquePtr<TestClass> testptr2(new TestClass());
	assert(testptr2.get() != nullptr);

	MyUniquePtr<TestClass> testptr3(testptr2);

	MyUniquePtr<TestClass> testptr4;
	testptr4 = testptr3;

	/*auto test = new TestClass();
	MyUniquePtr<TestClass> testptr_invalid(test);*/

}