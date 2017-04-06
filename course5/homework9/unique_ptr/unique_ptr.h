
#pragma once

#include <utility>

namespace Ptrs {

template<typename T>
class UniquePtr
{
public:
	explicit UniquePtr(T* ptr = nullptr): mPtr(ptr) { }
	UniquePtr(const UniquePtr<T>&) = delete;
	UniquePtr(UniquePtr<T>&& move)
	{
		*this = std::move(move);
	}

	UniquePtr& operator=(const UniquePtr&) = delete;
	UniquePtr& operator=(UniquePtr&& move)
	{
		mPtr = move.mPtr;
		move.mPtr = nullptr;
		return *this;
	}

	~UniquePtr() { delete mPtr; }

	void reset(T* ptr = nullptr)
	{
		delete mPtr;
		mPtr = ptr;
	}

	T* get() { return mPtr; }
	const T* get() const { return mPtr; }

	T* operator->() { return mPtr; }
	const T* operator->() const { return mPtr; }

	T& operator*() { return *mPtr; }
	const T& operator*() const { return *mPtr; }

	explicit operator bool() { return mPtr != nullptr; }
	bool operator!() { return mPtr == nullptr; }

private:
	T* mPtr = nullptr;
};

template<typename T, typename... Args>
UniquePtr<T> MakeUnique(Args&& ... args)
{
	return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

}
