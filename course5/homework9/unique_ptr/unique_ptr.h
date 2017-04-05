
#pragma once

#include <utility>

template<typename T>
class UniquePtr
{
public:
	UniquePtr(T* ptr): mPtr(ptr) { }
	~UniquePtr() { delete mPtr; }

	void reset(T* ptr = nullptr)
	{
		if (mPtr)
			delete mPtr;

		mPtr = ptr;
	}

	T* get() { return mPtr; }
	const T* get() const { return mPtr; }

	T* operator->() { return mPtr; }
	const T* operator->() const { return mPtr; }

private:
	T* mPtr = nullptr;
};

template<typename T, typename... Args>
UniquePtr<T> MakeUnique(Args&& ... args)
{
	return UniquePtr<T>(new T(std::forward<Args>(args)...));
}
