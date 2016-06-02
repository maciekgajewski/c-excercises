#include <iostream>
#include <stdexcept>

template<typename T>
class UniquePtr
{
public:
	UniquePtr() = default;
	UniquePtr(T* p) : mData(p) {}
	UniquePtr(UniquePtr&& other) : mData(other.mData) { other.mData = nullptr; }
	~UniquePtr() { delete mData; }
	
	const T& operator*() const { return *mData; }
	const T* operator->() const { return mData; }
	
	const T* get() const { mData; }
	
private:
	T* mData = nullptr;
};

template<typename T, typename... Args>
UniquePtr<T> MakeUnique(const Args&... args) // 'const Args&... args' => 'const int& args0, const char& args1'
{
	return UniquePtr<T>(new T(args...));// 'args...' => 'args0, args1'
}

template<typename U>
class UniquePtr<U[]>
{
public:
	UniquePtr(U* ptr) : mData(ptr) { }
	UniquePtr() = default;
	~UniquePtr() { delete[] mData; }
	UniquePtr(UniquePtr&& other) : mData(other.mData) { other.mData = nullptr; }
	
	U& operator[](std::size_t index) { return mData[index]; }
	
private:
	
	U* mData = nullptr;
};

int main()
{
	//UniquePtr<std::string> p(new std::string("Hello"));
	auto p = MakeUnique<std::string>(7, 'x');
	UniquePtr<std::string> copy = std::move(p);
	
	UniquePtr<std::string[]> array(new std::string[4]);
	
	std::cout << *copy << std::endl;
	std::cout << "length=" << copy->length() << std::endl;
	
	array[0] = "yo";
	std::cout << array[0] << std::endl;
}