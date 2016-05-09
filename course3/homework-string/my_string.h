#pragma once
#include <iostream>
#include <memory>
#include <cstring>

class MyString
{
	private:
		std::unique_ptr<char[]> buf;

	public:
		MyString() : buf(std::make_unique<char[]>(0)) {}

		MyString(const char* str) : buf(std::make_unique<char[]>(std::strlen(str))) {
			strcpy(buf.get(), str);
		}

		MyString(const MyString& obj) : buf(std::make_unique<char[]>(obj.size())) {
			strcpy(buf.get(), obj.buf.get());
		}

		bool operator== (const MyString& rhs) const {
			return std::strcmp(buf.get(), rhs.buf.get()) == 0;
		}

		bool operator!= (const MyString& rhs) const {
			return !operator==(rhs);
		}

		const char& operator[] (int i) const {
			return buf.get()[i];
		}

		char& operator[] (int i) {
			return buf.get()[i];
		}

		bool empty() const {
			return std::strlen(buf.get()) == 0;
		}

		int size() const {
			return std::strlen(buf.get());
		}
};
