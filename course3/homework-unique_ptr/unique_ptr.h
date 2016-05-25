#pragma once

#include <cstddef>
#include <utility>


namespace karun
{
	template <class T>
	class unique_ptr
	{	
		
	public:
		unique_ptr();
		unique_ptr(std::nullptr_t);
		explicit unique_ptr(T*);
		unique_ptr(unique_ptr<T>&&);
		~unique_ptr();
		
		unique_ptr<T>& operator=(std::nullptr_t);
		unique_ptr<T>& operator=(unique_ptr<T>&& ptr);
		
		T* get() const;
		void reset();
		void reset(std::nullptr_t);
		void reset(T* ptr);
		T* release();
		void swap(unique_ptr<T>& ptr);
		
		operator bool() const;
		T operator*() const;
		T* operator->() const;
		
		
		
		
	private:
		T* mPtr;
		
	};
}
