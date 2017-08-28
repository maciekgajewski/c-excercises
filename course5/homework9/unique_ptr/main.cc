
#include "unique_ptr.h"

#include <iostream>
#include <cassert>

class TestClass
{
public:
	explicit TestClass(int instanceNo): mInstanceNo(instanceNo)
	{
		std::cout << "Creating instance " << mInstanceNo << std::endl;
		++mInstanceCount;
	}

	TestClass(const TestClass&) = delete;
	TestClass(TestClass&&) = delete;
	TestClass& operator=(const TestClass&) = delete;
	TestClass& operator=(TestClass&&) = delete;

	~TestClass()
	{
		std::cout << "Deleting instance " << mInstanceNo << std::endl;
		--mInstanceCount;
	}

	int mInstanceNo;
	static int mInstanceCount;
};

int TestClass::mInstanceCount = 0;

int main()
{
	// Test MakeUnique, standard UniquePtr constructor,
	// operator-> and operator*
	Ptrs::UniquePtr<TestClass> ptr = Ptrs::MakeUnique<TestClass>(123);
	assert(ptr->mInstanceNo == 123);
	assert((*ptr).mInstanceNo == 123);
	assert(TestClass::mInstanceCount == 1);

	// Test .get()
	TestClass* raw1 = ptr.get();
	assert(raw1->mInstanceNo == 123);
	assert(TestClass::mInstanceCount == 1);

	// Test .reset(object)
	auto raw2 = new TestClass(456);
	assert(TestClass::mInstanceCount == 2);
	ptr.reset(raw2);
	assert(ptr->mInstanceNo == 456);
	assert(TestClass::mInstanceCount == 1);

	// Test empty .reset()
	ptr.reset();
	assert(TestClass::mInstanceCount == 0);

	// Test const constructor, operator-> and operator*
	const auto cptr = Ptrs::MakeUnique<TestClass>(789);
	assert(cptr->mInstanceNo == 789);
	assert((*cptr).mInstanceNo == 789);
	assert(TestClass::mInstanceCount == 1);

	// Test const .get
	const auto raw3 = cptr.get();
	assert(raw3->mInstanceNo == 789);

	// Test empty constructor
	Ptrs::UniquePtr<TestClass> ptr2;

	// Test operator!
	assert(!ptr2);
	auto ptr3 = Ptrs::MakeUnique<TestClass>(111);

	// Test operator=(UniquePtr&&)
	ptr2 = std::move(ptr3);

	// Test operator bool
	assert(ptr2);
	assert(!ptr);

	assert(ptr2->mInstanceNo == 111);
	assert(TestClass::mInstanceCount == 2);
}
