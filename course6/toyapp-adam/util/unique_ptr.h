#pragma once

#include <cassert>
#include <ostream>
#include <utility>

namespace Util {

template<typename Type>
class UniquePtr
{
public:
	template<typename... Args>
	static UniquePtr Make(Args&&... args)
	{
		return UniquePtr(std::forward<Args>(args)...);
	}

	UniquePtr()
	:	mPtr(nullptr)
	{}

	UniquePtr(UniquePtr&& other)
	:	mPtr(other.mPtr)
	{
		other.mPtr = nullptr;
	}

	UniquePtr& operator=(UniquePtr&& other)
	{
		if (this != &other)
		{
			delete mPtr;
			mPtr = other.mPtr;
			other.mPtr = nullptr;
		}
		return *this;
	}

	~UniquePtr()
	{
		delete mPtr;
	}

	UniquePtr(const UniquePtr&) = delete;
	UniquePtr& operator=(const UniquePtr&) = delete;

	Type& operator*()
	{
		assert(mPtr);
		return *mPtr;
	}

	const Type& operator*() const
	{
		assert(mPtr);
		return *mPtr;
	}

	Type* operator->()
	{
		assert(mPtr);
		return mPtr;
	}

	const Type* operator->() const
	{
		assert(mPtr);
		return mPtr;
	}

	operator Type*()
	{
		return mPtr;
	}

	operator const Type*() const
	{
		return mPtr;
	}

	friend std::ostream& operator<<(std::ostream& stream, const UniquePtr& ptr)
	{
		stream << ptr.mPtr;
		return stream;
	}

private:
	Type* mPtr;

	template<typename... Args>
	UniquePtr(Args&&... args)
	:	mPtr(new Type(std::forward<Args>(args)...))
	{}
};

}
