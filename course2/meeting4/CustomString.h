/*
 * CustomString.h
 *
 *  Created on: Jan 20, 2016
 *      Author: matthijs
 */

#ifndef CUSTOMSTRING_H_
#define CUSTOMSTRING_H_

#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

typedef std::unique_ptr<char[]> cstr_ptr;

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


class SmartString
{
public:
	SmartString() {}

	SmartString(const char* str) {
		initFromCstr(str);
	}

	SmartString(const SmartString& str) {
		initFromCstr(str.mChars.get());
	}

	size_t length() { return mLength; }

	/* operators on C-style strings */
	SmartString& operator=(const char* str) {
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
	SmartString& operator=(const SmartString& str) {
		initFromCstr(str.mChars.get());
		return *this;
	}
	const SmartString operator+(const SmartString& str) {
		SmartString r = *this;
		r += str;
		return r;
	}
	SmartString& operator+=(const SmartString& str) {
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
	bool operator==(const SmartString& str) {
		return std::strcmp(mChars.get(), str.mChars.get()) == 0;
	}
	bool operator!=(const SmartString& str) {
		return std::strcmp(mChars.get(), str.mChars.get()) != 0;
	}
	bool operator<(const SmartString& str) {
		return std::strcoll(mChars.get(), str.mChars.get()) < 0;
	}
	char& operator[](int i) {
		return mChars[i];
	}

	friend std::ostream& operator<<(std::ostream& os, const SmartString& str);


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

std::ostream& operator<<(std::ostream& stream, const SmartString& str) {
	stream.write(str.mChars.get(), str.mLength);
	return stream;
}

#endif /* CUSTOMSTRING_H_ */
