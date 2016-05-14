#include <iostream>
#include <cstring>
#include "my_string.h"

MyString::MyString(){
	buffer = std::unique_ptr<char[]>(new char[1]);
	buffer = '\0';
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
	if (buffer){
		return buffer[0] == 0 ? true : false ;
	}
	else true;
}

size_t MyString::size() const {
	if (buffer){
		return std::strlen(buffer.get());
	}
	else return 0;
}	

const bool MyString::operator == (const MyString& theString){
	if (buffer){
		return std::strcmp(buffer.get(), theString.buffer.get()) == 0 ? true : false;
	}
	else return false;
}

const bool MyString::operator != (const MyString& theString){
	if ( buffer && theString.buffer){
		return buffer.get() == theString.buffer.get() ? false : true ;
	}
	else if ( buffer == nullptr && theString.buffer == nullptr ){
		return true;
	}
	else return false;
}

char& MyString::operator[](int index) const{
	return buffer[index]; 
}
