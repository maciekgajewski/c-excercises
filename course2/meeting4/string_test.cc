#include <string>
#include <cstring>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

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

	CustomString(std::vector<char> str) {
		mChars = str;
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

	friend std::stringstream& operator<<(std::stringstream& os, const CustomString& str);


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

std::stringstream& operator<<(std::stringstream& stream, const CustomString& str) {
	for (std::vector<char>::const_iterator it = str.mChars.begin(); it != str.mChars.end(); ++it) {
		stream << *it;
	}
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
}
