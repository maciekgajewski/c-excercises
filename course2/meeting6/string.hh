#pragma once

#include <iostream>
#include <memory>
#include <cassert>
#include <cstring>
#include <sstream>

template<typename T>
class UP
{
public:
    UP(T* p) : mPtr(p) {}
    UP(const UP&) = delete;
    UP(UP&& other)
    {   
        delete mPtr;
        mPtr = other.mPtr;
        other.mPtr = nullptr;
    }
    ~UP() { delete mPtr; }
    
    T* get() { return mPtr; }
    const T* get() const { return mPtr; }
    
private:
    T* mPtr = nullptr;
};


class MyString
{
public:
	MyString() = default;
	MyString(const char* str)
	{
		mLength = std::strlen(str);
		if (mLength > 0)
		{
			mChars.reset(new char[mLength + 1]);
			std::strcpy(mChars.get(), str);
		}
	}

	MyString(const MyString& other)
	{
        std::cout << "copy!" << std::endl;
		mLength = other.mLength;
		if (mLength > 0)
		{
			mChars.reset(new char[mLength + 1]);
			std::strcpy(mChars.get(), other.mChars.get());
		}
	}
	
	MyString(MyString&& other) noexcept
	{
        // TODO
    }
	

	MyString& operator=(const MyString& other)
	{
        std::cout << "copy assignment!" << std::endl;
		mLength = other.mLength;
		if (mLength > 0)
		{
			mChars.reset(new char[mLength + 1]);
			std::strcpy(mChars.get(), other.mChars.get());
		}
		else
		{
			mChars.reset();
		}
		return *this;
	}
	
	
	MyString& operator=(MyString&& other)
    {
        std::cout <<"move assigment" << std::endl;
        mLength = other.mLength;
        mChars.swap(other.mChars);
        return *this;
    }
	
	MyString& operator=(const char* str)
	{
		mLength = std::strlen(str);
		if (mLength > 0)
		{
			mChars.reset(new char[mLength + 1]);
			std::strcpy(mChars.get(), str);
		}
		else
		{
			mChars.reset();
		}
		return *this;
	}
	
	MyString& operator+=(const MyString& other)
	{
		auto newLength = mLength + other.mLength;
		if (newLength > 0)
		{
			std::unique_ptr<char[]> newChars(new char[newLength+1]);
			if (mLength > 0)
			{
				std::strcpy(newChars.get(), mChars.get());
			}
			std::strcpy(newChars.get() + mLength, other.mChars.get());
			
			mLength = newLength;
			mChars = std::move(newChars);
		}
		return *this;
	}
	
	MyString operator+(const MyString& other)
	{
		MyString result;
		result.mLength = mLength + other.mLength;
		if (result.mLength > 0)
		{
			result.mChars.reset(new char[result.mLength+1]);
			std::strcpy(result.mChars.get(), mChars.get());
			std::strcpy(result.mChars.get() + mLength, other.mChars.get());
		}
		return result;
	}

	size_t length() const { return mLength; }

	bool operator==(const char* str)
	{
		return std::strcmp(c_str(), str) == 0;
	}
	
	bool operator!=(const char* str)
	{
		return std::strcmp(c_str(), str) != 0;
	}

	bool operator==(const MyString& str)
	{ 
		return std::strcmp(c_str(), str.c_str()) == 0;
	}
	
	bool operator!=(const MyString& str)
	{ 
		return std::strcmp(c_str(), str.c_str()) != 0;
	}
	
	bool operator<(const MyString& str)
	{
		return std::strcoll(c_str(), str.c_str()) < 0;
	}
	
	const char& operator[](int i) const
	{
		return mChars.get()[i];
	}
		
	char& operator[](int i)
	{
		return mChars.get()[i];
    }
    
	friend std::ostream& operator<<(std::ostream& os, const MyString& str)
	{
		if (str.mChars)
		{
			return os << str.mChars.get();
		}
		return os;
	}
	
	const char* c_str() const
	{
		if (mChars)
			return mChars.get();
		else
			return "";
	}

protected:
	std::unique_ptr<char[]> mChars; 
	size_t mLength = 0;

};
template<typename StringType>
void basic_test()
{
	// Default construction
	StringType s1;
	assert(s1.length() == 0);

	// Construction from c string
	StringType s2 = "Hello";
	assert(s2.length() == 5);
        
	// Copy creation
	StringType s3 = s2;
	assert(s3.length() == 5);
	assert(s2.length() == 5);
	
	// Assignment
	s1 = s3;
	assert(s3.length() == 5);
	assert(s2.length() == 5);
	assert(s1.length() == 5);
}

template<typename StringType>
void basic_operators()
{
	StringType slong = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	StringType s1 = "aaaaaa";
	StringType s2 = "zzzzz";
	StringType s3 = s1;
	
	// string - to - string operator
	assert(s1 == s3);
	assert(s1 != s2);
	assert(s1 < s2);
	
	// comparison witch const char*
	assert(s1 == "aaaaaa");
	assert(s2 != "aaaaaa");

	StringType empty;
	assert(empty != "aaa");
	assert(s1 != empty);
}

template<typename StringType>
void indexing_operator()
{
	// indexing operator
	StringType s1 = "abc";
	
	// accesing individual elements
	assert(s1[0] == 'a');
	assert(s1[1] == 'b');
	assert(s1[2] == 'c');
	
	// accesing element fomr outside of the range is undefined operation, so no rnage checks required
	
	// modifying characters
	s1[0] = 'x';
	s1[1] = 'y';
	s1[2] = 'z';
	assert(s1 == "xyz");
}

template<typename StringType>
void stream_output_operator()
{
	std::stringstream stream;
	
	StringType s1 = "Test";
	
	stream << s1;
	
	assert(stream.str() == "Test");
}

template<typename StringType>
void concatenation_operator()
{
	StringType slong = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	StringType s1 = "aa";
	StringType s2 = "bbb";
	
	// concatenation
	StringType s3 = s1 + s2;
	assert(s3 == "aabbb");
	assert(s1 == "aa");
	assert(s2 == "bbb");
	
	// appending
	s3 += s1;
	assert(s3 == "aabbbaa");

	s2 += slong;
	assert(s2 == "bbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
}

void test_string()
{
	basic_test<MyString>();
	basic_operators<MyString>();
	indexing_operator<MyString>();
	stream_output_operator<MyString>();
	concatenation_operator<MyString>();
	std::cout << "MyString tests passed" << std::endl;
}
