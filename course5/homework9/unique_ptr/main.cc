
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
	UniquePtr<TestClass> ptr = MakeUnique<TestClass>(123);
	assert(ptr->mInstanceNo == 123);
	assert(TestClass::mInstanceCount == 1);

	TestClass* raw1 = ptr.get();
	assert(raw1->mInstanceNo == 123);
	assert(TestClass::mInstanceCount == 1);

	auto raw2 = new TestClass(456);
	assert(TestClass::mInstanceCount == 2);

	ptr.reset(raw2);
	assert(ptr->mInstanceNo == 456);
	assert(TestClass::mInstanceCount == 1);

	ptr.reset();
	assert(TestClass::mInstanceCount == 0);

	const auto cptr = MakeUnique<TestClass>(789);
	assert(cptr->mInstanceNo == 789);
	assert(TestClass::mInstanceCount == 1);

	const auto raw3 = cptr.get();
	assert(raw3->mInstanceNo == 789);
}
