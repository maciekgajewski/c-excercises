#pragma once
#include <memory>
#include <iostream>
#include <cstring>

class MyString
{
private:
    std::unique_ptr<char[]> data;
public:
	MyString();  			// default constructor
	MyString(const char*);		// string literal constructor
	MyString(const MyString&);	// copy constructor	

	bool empty() const;
	int size() const;

	friend bool operator== (const MyString &s1, const MyString &s2); // equality operator is friended
	friend bool operator!=  (const MyString &s1, const MyString &s2);
	char& operator[](const int); // indexing operator
	char operator[](const int) const; // const indexing operator
};

MyString::MyString(){};

MyString::MyString(const char* inchar){
	int n = std::strlen(inchar) + 1;
	data = std::unique_ptr<char[]>(new char[n]);
 	std::strcpy(data.get(), inchar);
};

MyString::MyString(const MyString& that): data(new char[that.size()+1]){
	std::strcpy(data.get(), that.data.get());
}


bool MyString::empty() const{
	return size() == 0;
};

int MyString::size() const{
	if (data == 0)
		return 0;
	else
		return std::strlen(data.get());
};

bool operator==(const MyString &s1, const MyString &s2){
//	std::cout << "comparison operator " << s1.data.get()<< "==" << s2.data.get() << "?" << std::endl;
	return std::strcmp(s1.data.get(), s2.data.get()) == 0;
}

bool operator!=(const MyString &s1, const MyString &s2){
	return !(s1==s2);
}

char& MyString::operator[](const int i){
	return data.get()[i];
}

char MyString::operator[](const int i) const{
	return data.get()[i];
}
