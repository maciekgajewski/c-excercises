#pragma once

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
		MyUniquePtr() = default;
		MyUniquePtr(T* obj) : mData(obj) {}
		MyUniquePtr(const MyUniquePtr& obj) = delete;
		MyUniquePtr(MyUniquePtr&& obj) : mData(obj.mData) { obj.mData = nullptr; }
		~MyUniquePtr() { delete[] mData; }

		const T& operator*() const { return *mData; }
		const T* operator->() const { return mData; }
		const T* get() const { return mData; }
		const T& operator[](std::size_t index) const { return mData[index]; }
		T& operator[](std::size_t index) { return mData[index]; }

};

template<typename T, typename... Args>
MyUniquePtr<T> MyMakeUnique(const Args&... args)
{
	return MyUniquePtr<T>(new T(args...));
}
