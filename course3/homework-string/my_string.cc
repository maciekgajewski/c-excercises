#include <iostream>
#include <cstring>
#include "my_string.h"

MyString::MyString(){
	numberOfChars = 0;
}

MyString::MyString(const char* theString){
	numberOfChars = std::strlen(theString);
	buffer = std::unique_ptr<char[]>(new char[numberOfChars]);
	for (int i = 0; i < numberOfChars; i++){
		buffer[i] = theString[i];
	}
}

MyString::MyString(const MyString& theString){
	numberOfChars = theString.size();
	buffer = std::unique_ptr<char[]>(new char[numberOfChars]);
	for (int i = 0; i < numberOfChars; i++){
		buffer[i] = theString[i];
	}
}

bool MyString::empty() const {
	return numberOfChars == 0 ? true : false ;
}


int MyString::size() const {
	return numberOfChars;
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

