#include <cstddef>
#include <iostream>

template<class T>
class MyUniquePtr
{
public:
	MyUniquePtr() : mData(nullptr)
	{
		std::cout << "MyUniquePtr::ctor" << std::endl;
	}
	
	MyUniquePtr(MyUniquePtr& that)
	{
		// Construction one unique pointer from another simply changes the ownership of the data
		mData = that.mData;
		that.mData = nullptr;
		std::cout << "MyUniquePtr::Copy" << std::endl;
	}
	
	MyUniquePtr(T*&& data) : mData(data)
	{
		// Constructing from an r-value means we aquire ownership of the data
		std::cout << "MyUniquePtr::MoveData" << std::endl;
	}

	~MyUniquePtr()
	{
		std::cout << "MyUniquePtr::Destruct" << std::endl;

		if (mData != nullptr)
		{
			// If we currently own any data delete it
			std::cout << "MyUniquePtr::Cleaning data" << std::endl;
			delete mData;
		}
	}

	MyUniquePtr& operator = (MyUniquePtr& arg)
	{
		// Assigning one unique pointer to another simply changes the ownership of the data
		mData = arg.mData;
		arg.mData = nullptr;
		return *this;
	}

	bool operator == (const MyUniquePtr<T>& that) const
	{
		// Pointer is unique, can't ever be equal to anything
		return false;
	}

	bool operator == (const std::nullptr_t that) const
	{
		// Except the special case of the nullptr
		return mData == that;
	}

	operator bool() const
	{
		return mData != nullptr;
	}

	T* get() const
	{
		return mData;
	}

	void reset(T*&& data)
	{
		if (mData != nullptr)
			delete mData;

		mData = data;
	}

	T* release()
	{
		auto data = mData;
		mData = nullptr;
		return data;
	}

	void swap(MyUniquePtr<T>& that)
	{
		auto temp = mData;
		mData = that.mData;
		that.mData = temp;
	}

private:
	T* mData;
};