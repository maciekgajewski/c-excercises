#include <iostream>
#include <string>

template<typename T>
struct PtrDetector
{
	static const bool IsPointer = false;
	using WithoutPtr = T;
};

template<typename P>
struct PtrDetector<P*>
{
	static const bool IsPointer = true;
	using WithoutPtr = P;
};

template<typename V>
void foo(V v)
{
	using VNotPtr = PtrDetector<int>::WithoutPtr;
}

int main()
{
	auto b1 = PtrDetector<int>::IsPointer;
	auto b2 = PtrDetector<int*>::IsPointer;
	
	using T1 = PtrDetector<int>::WithoutPtr;
	using T2 = PtrDetector<int*>::WithoutPtr;
}