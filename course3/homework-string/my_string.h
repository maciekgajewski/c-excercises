#pragma once
#include <iostream>
#include <memory>
#include <cstring>

class MyString
{
	private:
		std::unique_ptr<char[]> buf;

	public:
		MyString(const char* str) {
			std::cout << "String literal constructor" << std::endl;
			buf = std::make_unique<char[]>(std::strlen(str));
			strcpy(buf.get(), str);
		}

		MyString() {
			std::cout << "Default constructor" << std::endl;
			buf = std::make_unique<char[]>(0);
		}

		MyString(const MyString& obj){
			std::cout << "Copy constructor" << std::endl;
			buf = std::make_unique<char[]>(obj.size());
			strcpy(buf.get(), obj.buf.get());
		}

		~MyString() {
			std::cout << "Destructor" << std::endl;
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
