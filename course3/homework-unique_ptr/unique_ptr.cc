#include "unique_ptr.h"


template<class T>
karun::unique_ptr<T>::unique_ptr() : mPtr(nullptr) {}

template<class T>
karun::unique_ptr<T>::unique_ptr(std::nullptr_t) : mPtr(nullptr) {}

template<class T>
karun::unique_ptr<T>::unique_ptr(T* ptr) : mPtr(ptr) {}

template<class T>
karun::unique_ptr<T>::unique_ptr(karun::unique_ptr<T>&& ptr)
	: mPtr(ptr.mPtr)
{
	ptr.mPtr = nullptr;
}

template<class T>
karun::unique_ptr<T>::~unique_ptr() 
{
	delete mPtr;
}

template<class T>
karun::unique_ptr<T>& karun::unique_ptr<T>::operator=(std::nullptr_t)
{
	reset(nullptr);
	return *this;
}

template<class T>
karun::unique_ptr<T>& karun::unique_ptr<T>::operator=(karun::unique_ptr<T>&& ptr)
{
	reset(ptr.mPtr);
	ptr.mPtr = nullptr;
	return *this;
}

template<class T>
T* karun::unique_ptr<T>::get() const
{
	return mPtr;
}

template<class T>
void karun::unique_ptr<T>::reset()
{
	reset(nullptr);
}

template<class T>
void karun::unique_ptr<T>::reset(std::nullptr_t)
{
	delete mPtr;
	mPtr = nullptr;
}

template<class T>
void karun::unique_ptr<T>::reset(T* ptr)
{
	delete mPtr;
	mPtr = ptr;
}

template<class T>
T* karun::unique_ptr<T>::release()
{
	T* ptr = mPtr;
	mPtr = nullptr;
	return ptr;
}

template<class T>
void karun::unique_ptr<T>::swap(karun::unique_ptr<T>& ptr)
{
	std::swap(mPtr, ptr.mPtr);
}

template<class T>
karun::unique_ptr<T>::operator bool() const
{
	return mPtr != nullptr;
}

template<class T>
T karun::unique_ptr<T>::operator*() const
{
	return *mPtr;
}

template<class T>
T* karun::unique_ptr<T>::operator->() const
{
	return mPtr;
}

template<class T>
bool karun::unique_ptr<T>::operator==(const unique_ptr<T>& ptr) const
{
	return mPtr == ptr.mPtr;
}

template<class T>
bool karun::unique_ptr<T>::operator!=(const unique_ptr<T>& ptr) const
{
	return mPtr != ptr.mPtr;
}
