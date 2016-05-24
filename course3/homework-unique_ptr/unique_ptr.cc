#include "unique_ptr.h"


template<class T>
karun::unique_ptr<T>::~unique_ptr()
{
	if (mPtr) delete mPtr;
}

template<class T>
T* karun::unique_ptr<T>::get() const
{
	return mPtr;
}

template<class T>
T* karun::unique_ptr<T>::release()
{
	T* tempPtr = mPtr;
	mPtr = nullptr;
	return tempPtr;
}

template<class T>
void karun::unique_ptr<T>::reset()
{
	reset(nullptr);
}

template<class T>
void karun::unique_ptr<T>::reset(T* ptr)
{
	if (mPtr) delete mPtr;
	mPtr = ptr;
}

template<class T>
void karun::unique_ptr<T>::swap(unique_ptr<T>& ptr)
{
	T* tempPtr = mPtr;
	mPtr = ptr.mPtr;
	ptr.mPtr = tempPtr;
}

template<class T>
karun::unique_ptr<T>::operator bool() const
{
	return mPtr != nullptr;
}
