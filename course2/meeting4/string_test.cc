#include <string>
#include <cstring>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <memory>

typedef std::unique_ptr<char[]> cstr_ptr;

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
}

class CustomString
{
public:
	CustomString() {}

	CustomString(const char* str) {
		copyCharArray(str);
	}

	int length() { return mChars.size(); }

	/* operators on C-style strings */
	CustomString& operator=(const char* str) {
		mChars.clear();
		copyCharArray(str);
		return *this;
	}

	bool operator==(const char* str) {
		return compareCharArray(str);
	}
	bool operator!=(const char* str) {
		return !compareCharArray(str);
	}

	/* operators on CustomStrings */
	CustomString& operator=(const CustomString& str) {
		mChars = str.mChars;
		return *this;
	}
	const CustomString operator+(const CustomString& str2) {
		CustomString r = *this;
		r += str2;
		return r;
	}
	CustomString& operator+=(const CustomString& str) {
		mChars.insert(mChars.end(), str.mChars.begin(), str.mChars.end());
		return *this;
	}
	bool operator==(const CustomString& str) {
		return mChars == str.mChars;
	}
	bool operator!=(const CustomString& str) {
		return mChars != str.mChars;
	}
	bool operator<(const CustomString& str) {
		return mChars < str.mChars;
	}
	char& operator[](int i) {
		return mChars[i];
	}

	friend std::ostream& operator<<(std::ostream& os, const CustomString& str);


private:
	std::vector<char> mChars;

	void copyCharArray(const char* str) {
		for ( int i = 0; str[i] != '\0'; i++ ) {
			mChars.push_back(str[i]);
		}
	}

	bool compareCharArray(const char* str) {
		//unsigned to make compiler warning go away
		unsigned int len = std::strlen(str);
		if ( len != mChars.size() ) {
			return false;
		}
		for ( unsigned int i = 0; i < len; i++ ) {
			if ( mChars[i] != str[i] ) {
				return false;
			}
		}
		return true;
	}

};

std::ostream& operator<<(std::ostream& stream, const CustomString& str) {
	stream.write(str.mChars.data(), str.mChars.size());
	return stream;
}


class CustomString2
{
public:
	CustomString2() {}

	CustomString2(const char* str) {
		initFromCstr(str);
	}

	CustomString2(const CustomString2& str) {
		initFromCstr(str.mChars.get());
	}

	size_t length() { return mLength; }

	/* operators on C-style strings */
	CustomString2& operator=(const char* str) {
		initFromCstr(str);
		return *this;
	}
	bool operator==(const char* str) {
		return std::strcmp(mChars.get(), str) == 0;
	}
	bool operator!=(const char* str) {
		return std::strcmp(mChars.get(), str) != 0;
	}

	/* operators on CustomString2s */
	CustomString2& operator=(const CustomString2& str) {
		initFromCstr(str.mChars.get());
		return *this;
	}
	const CustomString2 operator+(const CustomString2& str) {
		CustomString2 r = *this;
		r += str;
		return r;
	}
	CustomString2& operator+=(const CustomString2& str) {
		mLength += str.mLength;
		cstr_ptr temp( new char[mLength + 1] );
		std::strcpy(temp.get(), mChars.get());
		std::strcat(temp.get(), str.mChars.get());
		// I don't understand why I have to use move here while in initFromCstr
		// I can use direct assignment; i.e. why is the operation in initFromCstr
		// a move assignment while the below (without std::move) is a copy assignment?
		mChars = std::move(temp);
		return *this;
	}
	bool operator==(const CustomString2& str) {
		return std::strcmp(mChars.get(), str.mChars.get()) == 0;
	}
	bool operator!=(const CustomString2& str) {
		return std::strcmp(mChars.get(), str.mChars.get()) != 0;
	}
	bool operator<(const CustomString2& str) {
		return std::strcoll(mChars.get(), str.mChars.get()) < 0;
	}
	char& operator[](int i) {
		return mChars[i];
	}

	friend std::ostream& operator<<(std::ostream& os, const CustomString2& str);


private:
	cstr_ptr mChars;
	size_t mLength = 0;

	void initFromCstr(const char* str) {
		mLength = std::strlen(str);
		/* Can do this since = is overloaded for unique_ptr.
		 * 1. Memory allocation for char array with length mLength+1
		 * 2. Construction of array
		 * 3. Memory allocation of cstr_ptr
		 * 4. Construction of cstr_ptr, acquires ownership of memory in steps 1+2
		 * 5. Memory owned by mChars is freed
		 * 6. mChars acquires ownership of rhs
		 * 7. rhs becomes nullpointer and is deleted once out of scope (function end)
		 */
		mChars = cstr_ptr( new char[mLength+1] );
		std::strcpy(mChars.get(), str);
	}
};

std::ostream& operator<<(std::ostream& stream, const CustomString2& str) {
	// Originally I put str.mLength+1 here, but then the assertion failed. So
	// apparently stream.str == "Bla" does not check null character?
	stream.write(str.mChars.get(), str.mLength);
	return stream;
}

int main()
{
//	basic_test<std::string>();
//	basic_operators<std::string>();
//	indexing_operator<std::string>();
//	stream_output_operator<std::string>();
//	concatenation_operator<std::string>();
//	std::cout << "std::string tests passed" << std::endl;
	
	// TODO after implementing your string class, run the selected functions for your type here
	basic_test<CustomString>();
	basic_operators<CustomString>();
	indexing_operator<CustomString>();
	stream_output_operator<CustomString>();
	concatenation_operator<CustomString>();
	std::cout << "CustomString tests passed" << std::endl;

	CustomString s("yoyo");
	assert(s == CustomString("yoyo"));
	assert(s == CustomString("yo") + CustomString("yo"));

	basic_test<CustomString2>();
	basic_operators<CustomString2>();
	indexing_operator<CustomString2>();
	stream_output_operator<CustomString2>();
	concatenation_operator<CustomString2>();
	std::cout << "CustomString2 tests passed" << std::endl;
}
