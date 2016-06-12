#pragma once
#include <type_traits>
#include <utility>
#include <cstddef>
#include <iostream>

template<typename T>
class MyUniquePtr
{
	private:
		T* mData = nullptr;

	public:
		MyUniquePtr() = default;
		MyUniquePtr(T* obj) : mData(obj) {}
		MyUniquePtr(const MyUniquePtr& obj) = delete;
		MyUniquePtr(MyUniquePtr&& obj) : mData(obj.mData) { obj.mData = nullptr; }
		~MyUniquePtr() { delete mData; }

		const T& operator*() const { return *mData; }
		const T* operator->() const { return mData; }
		const T* get() const { return mData; }
};

template<typename T>
class MyUniquePtr<T[]>
{
	private:
		T* mData = nullptr;

	public:
		//MyUniquePtr() = default;
		MyUniquePtr() : mData(nullptr) {
			std::cout << "MyUniquePtr[] default constructor" << std::endl;
		}
		MyUniquePtr(T* obj) : mData(obj) {
			std::cout << "MyUniquePtr[] initializing constructor" << std::endl;
		}
		MyUniquePtr(const MyUniquePtr& obj) = delete;
		MyUniquePtr(MyUniquePtr&& obj) : mData(obj.mData) {
			std::cout << "MyUniquePtr[] move constructor" << std::endl;
			obj.mData = nullptr;
		}
		~MyUniquePtr() {
			std::cout << "MyUniquePtr[] destructor" << std::endl;
			delete[] mData;
		}

		const T& operator*() const { return *mData; }
		const T* operator->() const { return mData; }
		const T* get() const { return mData; }
		T* get() { return mData; }
		const T& operator[](std::size_t index) const { return mData[index]; }
		T& operator[](std::size_t index) { return mData[index]; }
		void operator=(MyUniquePtr&& rhs) {
			mData = rhs.mData;
			rhs.mData = nullptr;
		}
		void reset() {
			delete[] mData;
			mData = nullptr;
		}

};

template<class T>
/* When I use std::size_t instead of int my unbounded array make_unique_ptr function
 * isn't called, the single object function is called instead. This results in
 * compilation errors naturally...dunno why the correct template function isn't being
 * inferred.*/
MyUniquePtr<T> MyMakeUnique(int num_entries)
{
	std::cout << "MyMakeUnique[] new" << std::endl;
	return MyUniquePtr<T>(new typename std::remove_extent<T>::type[num_entries]());
}

template<class T, class... Args>
MyUniquePtr<T> MyMakeUnique(Args&&... args)
{
	std::cout << "MyMakeUnique new" << std::endl;
	return MyUniquePtr<T>(new T(std::forward<Args>(args)...));
}
