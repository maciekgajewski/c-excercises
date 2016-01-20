/*
 * SmartString.h
 *
 *  Created on: Jan 20, 2016
 *      Author: matthijs
 */

#ifndef SMARTSTRING_H_
#define SMARTSTRING_H_

#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

typedef std::unique_ptr<char[]> cstr_ptr;

size_t INIT_CAPACITY = 100;
double INCREMENT_FACTOR = 1.5;

/* Basic operations */
class StringBase
{
public:
	StringBase() {}

	size_t length() { return mLength; }

	/* operators on c string */
	bool operator==(const char* str) {
		return std::strcmp(mChars.get(), str) == 0;
	}
	bool operator!=(const char* str) {
		return std::strcmp(mChars.get(), str) != 0;
	}

	/* operators on StringBase */
	bool operator==(const StringBase& str) {
		return std::strcmp(mChars.get(), str.mChars.get()) == 0;
	}
	bool operator!=(const StringBase& str) {
		return std::strcmp(mChars.get(), str.mChars.get()) != 0;
	}
	bool operator<(const StringBase& str) {
		return std::strcoll(mChars.get(), str.mChars.get()) < 0;
	}
	char& operator[](int i) {
		return mChars[i];
	}

	friend std::ostream& operator<<(std::ostream& os, const StringBase& str);

protected:
	cstr_ptr mChars;
	size_t mLength = 0;

};

std::ostream& operator<<(std::ostream& stream, const StringBase& str) {
	stream.write(str.mChars.get(), str.mLength);
	return stream;
}


class SmartString: public StringBase
{
public:
	SmartString() {}

	SmartString(const char* str) {
		initFromCstr(str);
	}

	SmartString(const SmartString& str) {
		initFromCstr(str.mChars.get(), str.mLength);
	}

	size_t capacity() { return mCapacity; }

	/* operators on C-style strings */
	SmartString& operator=(const char* str) {
		initFromCstr(str);
		return *this;
	}

	/* operators on SmartString */
	SmartString& operator=(const SmartString& str) {
		if ( &str != this ) {
			initFromCstr(str.mChars.get(), str.mLength);
		}
		return *this;
	}
	const SmartString operator+(const SmartString& str) {
		SmartString r = *this;
		r += str;
		return r;
	}
	SmartString& operator+=(const SmartString& str) {
		copy(str.mChars.get(), mLength, mLength + str.mLength);
		return *this;
	}

protected:
	size_t mCapacity = INIT_CAPACITY;

	void initFromCstr(const char* str, size_t strlen = 0) {
		copy(str, 0, strlen == 0 ? std::strlen(str) : strlen);
	}

	void copy(const char* src, size_t offset, size_t len) {
		checkCapacityIncrement(len);
		std::strcpy(mChars.get() + offset, src);
		mLength = len;
	}

	void checkCapacityIncrement(size_t len) {
		// it's either this increment var or another if. not sure which is better
		size_t increment = 0;
		if ( mCapacity < len + 1 ) {
			increment = (size_t) (INCREMENT_FACTOR-1)*len;
		}
		if ( mLength == 0 ) {
			mChars = cstr_ptr( new char[mCapacity + increment] );
		} else if ( increment > 0 ) {
			cstr_ptr temp( new char[mCapacity] );
			std::strcpy(temp.get(), mChars.get());
			mChars = std::move(temp);
		}
		mCapacity += increment;
	}
};



#endif /* SMARTSTRING_H_ */
