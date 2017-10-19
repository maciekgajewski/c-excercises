#include <iostream>
#include <string>
#include <memory>

struct Record
{
	Record() { std::cout << "Record(), this=" << this << std::endl; }
	Record(int x) { id = x; std::cout << "Record(int), this=" << this << std::endl; }
	~Record() { std::cout << "~Record(), this=" << this << std::endl; }
	
	std::string name;
	int id;
	float factor;
};

Record global;

Record* recordFactory(int x)
{
	global.id = x;
	return &global;
}

int main(int argc, char** argv)
{
	Record* datumPtr = recordFactory(77);
	datumPtr->name = "Hello 1234567890 1234567890";

	std::shared_ptr<Record> shared = std::make_shared<Record>(8);
	std::shared_ptr<Record> another = shared;


	Record x;
	Record* xptr = &x;

	std::cout << datumPtr->name << std::endl;
	delete datumPtr;
}

