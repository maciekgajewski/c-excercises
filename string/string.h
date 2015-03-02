#pragma once
#include <iostream>
#include <memory>

class String
{
public:
	using value_type = char;						// Every good behaving container should define 'value_type' type, which is the type of elements stored within
	using iterator = char*;							// Iteratore types
	using const_iterator = const char*;				// Feel free to use different types for iterators
	
	String();										// Default constructor, creates empty string. Should be cheap and perform no memory allocation
	~String();										// Destructor should free all allocated memory

	String(const String& o);						// Performs deep-copy of another string
	String(String&& o);								// Moves content from another string
	String(const char* s);							// Initializes string with the content of c-string. Assumes 's' is not null.
													// I repeat: ASSUMES 's' IS NOT NULL. Do not check if s is null. You may use 'assert', but that's it.
    String(const String& str, 						// Copies the portion of str that begins at the character position pos and spans len characters
            size_t pos, size_t len);
    String(const char* s, size_t n);				// Copies the null-terminated character sequence (C-string) pointed by s.
    String(size_t n, char c);						// Fills the string with n consecutive copies of character c.
	
    //template<typename It>							// Initializes string with a range (described by a pair of iterators).
    //	String(It first, It last);					// Allows for initializing with a content of another container containing characters (or compatible type)
	
	std::size_t size() const;						// Returns length of the string, in characters.
	
	bool empty() const;								// Returns 'true' is string is empty, 'false' otherwise.
	const char* c_str() const;						// Returns a pointer to null-terminated character array, usable in C functions.
													// The pointer may only be valid until the string is destroyed or modified.
																
	char operator[](std::size_t pos) const;			// Returns a character at specified positon in the string. Assumes pos < size()
	char& operator[](std::size_t pos);				// Returns a reference to a character at specified positon in the string. Assumes pos < size()
	
	iterator begin();								// Returns writable iterator to the begining of sequence. In case of empty string, returns the same value as end()
	iterator end();									// Returns past-the end iterator.

	const_iterator begin() const;					// Returns read-only iterator to the beginning of the sequence. For empty string, returns the same as end() const
	const_iterator end() const;						// Returns read-only past-the end iterator.
	
	void clear();									// Clears any content. After calling: empty() => true, size() => 0
	void swap(String& other);						// Swaps content with another instance. Should be fast, O(1) operation.

	String& operator = (const String& s);			// Assigns content of another string. Returns *this
	String& operator = (const char* s);				// Assigns content of C-string. Assumes s is not null returns *this
	String& operator = (String&& s);				// Moves away content from another rvalue instance

	bool operator==(const String& s) const;			// Compares with another string
	bool operator==(const char* s) const;			// Compares with c-string. Assumes s is not null

    char at(size_t pos) const;                      // Returns a reference to the character at position pos in the string.

private:
    std::unique_ptr<char[]> DATA;                   // Main container
    size_t len;                                     // Holds the size of the string
    void allocate(size_t size);                     // Allocates necessary memory
    void terminate();                               // Terminates string with zero char

	friend std::ostream& operator << 				// Stream output operator
		(std::ostream & stream, const String &str);	
	friend String operator+ 						// Concatenates strings
		(const String& a, const String& b);
};
