#include <string>
#include <cstdio>

// ARS -- week 04. 20170227

const std::string Endl ="\n";

class Stream
{
private:
	FILE*	m_fileptr = nullptr; 
public:
	Stream(const char* file);
	Stream(FILE*  stream);
	~Stream();
	Stream& operator << (int x);
	Stream& operator << (long l);
	Stream& operator << (bool b);
	Stream& operator << (char c);
	Stream& operator << (float f);
	Stream& operator << (double d);
	Stream& operator << (const char* str);
	Stream& operator << (std::string s);
};


/* 
Copyable? 
   A copy constructor for a stream is technically possible, but practically not wise, as
   you will have 2 objects having the same file descriptor. If the one objects is destructed, the
   other is stuck with an invalid filepointer. A possibility would be to have the copy contructor not
   copy the filepointer, but open the file with its own filepointer or dup() the other, but again, 
   synchronizing might become an issue

Default constructable?
   Why not, if the definition e.g. states that it will write to stdout as a default?

Movable
   Unlike copyable, I think a move contructor makes sense, as it moves all the resources from the src, 
   thereby preventing syncing issues, like with the copy
*/
