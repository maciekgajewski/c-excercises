#pragma once


namespace karun
{
	template <class T>
	class unique_ptr
	{	
		
	public:
		unique_ptr() = default;
		unique_ptr(unique_ptr<T>&) = delete;
		~unique_ptr();
		
		T* get() const;
		T* release();
		void reset();
		void reset(T* ptr);
		void swap(unique_ptr<T>& ptr);
		
		operator bool() const; 
		
	private:
		T* mPtr = nullptr;
		
	};
}
