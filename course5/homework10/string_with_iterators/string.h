#pragma once

#include <memory>
#include <ostream>

#include <iostream>

namespace String {

class String
{
public:
	String() = default;
	~String() = default;
	String(const String&);
	String(String&&);
	String& operator=(const String&);
	String& operator=(String&&);

	String(const char*);
	String& operator=(const char*);

	String operator+(const String&);
	String& operator+=(const String&);

	char& operator[](const size_t idx);
	const char& operator[](const size_t idx) const;

	bool operator==(const String&) const;
	bool operator!=(const String& rhs) const { return !(*this == rhs); }

	const char* c_str() const { return mSize > 0 ? mContents.get() : ""; }
	size_t length() const { return mSize > 0 ? mSize - 1 : 0; }

	template <typename T>
	class StringIterator:
		public std::iterator<std::random_access_iterator_tag, T, int, T*, T>
	{
	public:
		// For many of these operators I am not 100% sure which types to use
		explicit StringIterator(char* ptr): mPtr(ptr) { }
		StringIterator& operator++() { ++mPtr; inc(); return *this; }
		StringIterator& operator+(int rhs) { mPtr += rhs; inc(rhs); return *this; }
		void operator+=(int rhs) { mPtr += rhs; inc(rhs); }
		StringIterator& operator--(int rhs) { --mPtr; dec(); return *this; }
		StringIterator& operator-(int rhs) { mPtr -= rhs; inc(-rhs); return *this; }
		void operator-=(int rhs) { mPtr -= rhs; inc(-rhs); }
		bool operator==(StringIterator& rhs) const { return mPtr == rhs.mPtr; }
		bool operator!=(StringIterator& rhs) const { return !(*this == rhs); }
		T& operator*() { return *mPtr; }

		// Needed for std::find()
		size_t operator-(StringIterator& rhs) const { return reinterpret_cast<size_t>(mPtr) - reinterpret_cast<size_t>(rhs.mPtr); }
		T& operator>>(size_t amount) { return reinterpret_cast<size_t>(mPtr) >> amount; }

	private:
		char* mPtr;

		void inc() { std::cout << "Incrementing" << std::endl; }
		void dec() { std::cout << "Decrementing" << std::endl; }
		void inc(int i) { std::cout << "Incrementing by " << i << std::endl; }
	};

	using Iterator = StringIterator<char>;
	using Const_iterator = StringIterator<const char>;

	Iterator begin() { return Iterator(&mContents[0]); }
	Iterator end() { return Iterator(&mContents[mSize]); }

	Const_iterator begin() const { return Const_iterator(&mContents[0]); }
	Const_iterator end() const { return Const_iterator(&mContents[mSize]); }

private:
	size_t mSize = 0;
	std::unique_ptr<char[]> mContents;
};

inline std::ostream& operator<<(std::ostream& s, const String& str)
{
	s << str.c_str();
	return s;
}

}
