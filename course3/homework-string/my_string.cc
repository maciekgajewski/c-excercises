#include <iostream>
#include <cstring>
#include "my_string.h"

MyString::MyString(){
	buffer = std::unique_ptr<char[]>(new char[0]);
}

MyString::MyString(const char* theString){
	buffer = std::unique_ptr<char[]>(new char[std::strlen(theString)]);
	for (int i = 0; i < std::strlen(theString); i++){
		buffer[i] = theString[i];
	}
}

MyString::MyString(const MyString& theString){
	buffer = std::unique_ptr<char[]>(new char[theString.size()]);
	for (int i = 0; i < theString.size(); i++){
		buffer[i] = theString[i];
	}
}

bool MyString::empty() const {
	return size() == 0 ? true : false ;
}

int MyString::size() const {
	return std::strlen(buffer.get());
}	

const bool MyString::operator == (const MyString& theString){
	return std::strcmp(buffer.get(), theString.buffer.get()) == 0 ? true : false;
}

const bool MyString::operator != (const MyString& theString){
	return buffer == theString.buffer ? false : true ;
}

char& MyString::operator[](int index) const{
	return buffer[index]; 
}
