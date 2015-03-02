#pragma once
#include <iostream>
#include <memory>

class String
{
public:
    // Every good behaving container should define 'value_type' type, which is the type of elements stored within
    using value_type = char;
    // Iteratore types
    using iterator = char*;
    // Feel free to use different types for iterators
    using const_iterator = const char*;
	
    // Default constructor, creates empty string. Should be cheap and perform no memory allocation
    String();
    // Destructor should free all allocated memory
    ~String();
	// Performs deep-copy of another string
	String(const String& o);		
	// Moves content from another string	
	String(String&& o);	
	// Initializes string with the content of c-string. Assumes 's' is not null.
	// I repeat: ASSUMES 's' IS NOT NULL. Do not check if s is null. You may use 'assert', but that's it.		
	String(const char* s);							
	// Copies the portion of str that begins at the character position pos and spans len characters			
    String(const String& str, size_t pos, size_t len);
	// Copies the null-terminated character sequence (C-string) pointed by s.
    String(const char* s, size_t n);	
	// Fills the string with n consecutive copies of character c.	
    String(size_t n, char c);						
	
	// Initializes string with a range (described by a pair of iterators).
	// Allows for initializing with a content of another container containing characters (or compatible type)
    //template<typename It>							
    //	String(It first, It last);					
	
	// Returns length of the string, in characters.
	std::size_t size() const;						
	
	// Returns 'true' is string is empty, 'false' otherwise.
	bool empty() const;		
	// Returns a pointer to null-terminated character array, usable in C functions.
	// The pointer may only be valid until the string is destroyed or modified.
	const char* c_str() const;						
													
	// Returns a character at specified position in the string. Assumes pos < size()															
	char operator[](std::size_t pos) const;	
	// Returns a reference to a character at specified position in the string. Assumes pos < size()	
	char& operator[](std::size_t pos);	
	
	// Returns writeable iterator to the beginning of sequence. In case of empty string, returns the same value as end()
	iterator begin();		
	// Returns past-the end iterator.	
	iterator end();		
	
	// Returns read-only iterator to the beginning of the sequence. For empty string, returns the same as end() const
	const_iterator begin() const;	
	// Returns read-only past-the end iterator.	
	const_iterator end() const;						
	
	// Clears any content. After calling: empty() => true, size() => 0
	void clear();	
	// Swaps content with another instance. Should be fast, O(1) operation.	
	void swap(String& other);						

	// Assigns content of another string. Returns *this
	String& operator = (const String& s);	
	// Assigns content of C-string. Assumes s is not null returns *this	
	String& operator = (const char* s);		
	// Moves away content from another value instance	
	String& operator = (String&& s);				

	// Compares with another string
	bool operator==(const String& s) const;		
	// Compares with c-string. Assumes s is not null	
	bool operator==(const char* s) const;			

	// Returns a reference to the character at position pos in the string.
    char at(size_t pos) const;                      

private:
	// Main container
    std::unique_ptr<char[]> DATA;
	// Holds the size of the string
    size_t len;         
	// Allocates necessary array	
    void allocate(size_t size);     
	// Terminates string with zero char	
    void terminate();                               

	// Stream output operator
	friend std::ostream& operator << (std::ostream & stream, const String &str);

	// Concatenates strings	
	friend String operator+ (const String& a, const String& b);
};
