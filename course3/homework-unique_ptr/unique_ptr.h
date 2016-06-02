#pragma once

#include <cstddef>
#include <utility>


namespace karun
{
	template <class T>
	class unique_ptr
	{	
		
	public:
		unique_ptr() = default;
		explicit unique_ptr(T* ptr) : mPtr(ptr) {}
		unique_ptr(unique_ptr&& ptr) : mPtr(ptr.mPtr) { ptr.mPtr = nullptr; }
		~unique_ptr() { delete mPtr; }
		
		unique_ptr& operator=(std::nullptr_t)
		{
			reset(nullptr);
			return *this;
		}
		unique_ptr& operator=(unique_ptr&& ptr)
		{
			reset(ptr.mPtr);
			ptr.mPtr = nullptr;
			return *this;
		}
		
		T* get() const { return mPtr; }
		
		void reset() { reset(nullptr); }
		void reset(std::nullptr_t) 
		{ 
			delete mPtr; 
			mPtr = nullptr; 
		}
		void reset(T* ptr)
		{
			delete mPtr;
			mPtr = ptr;
		}
		
		T* release()
		{
			T* ptr = mPtr;
			mPtr = nullptr;
			return ptr;
		}
		
		void swap(unique_ptr& ptr) { std::swap(mPtr, ptr.mPtr); }
		
		operator bool() const { return mPtr != nullptr; }
		bool operator==(const unique_ptr<T>& ptr) const { return mPtr == ptr.mPtr; }
		bool operator!=(const unique_ptr<T>& ptr) const { return mPtr != ptr.mPtr; }
		T operator*() const { return *mPtr; }
		T* operator->() const { return mPtr; }
		
	private:
		T* mPtr = nullptr;
		
	};
}
