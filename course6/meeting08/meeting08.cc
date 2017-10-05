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

int main(int argc, char** argv)
{
	std::unique_ptr<Record> datumPtr = std::make_unique<Record>(77);
	datumPtr->name = "Hello 1234567890 1234567890";

	std::unique_ptr<Record[]> a = std::make_unique<Record[]>(3);
	a[1].name = "qwertyuiopasdfghjklzxcvbnm,.";

	Record b[3]

	b[1].name = "zzzzzzzzzzzzzzzzzzzzzz";

	std::cout << datumPtr->name << std::endl;
	std::cout << a[1].name << std::endl;
}

