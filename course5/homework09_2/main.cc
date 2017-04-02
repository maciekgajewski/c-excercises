/*
Write a simple single-object implementation of std::unique_ptr, complete with make_unique.
*/
#include <iostream>
#include <string>
#include <cassert>


// operators new/delete or new[]/delete[]

template<typename T>
struct MoreUniquePtr
{
	MoreUniquePtr() = default;
	MoreUniquePtr(const T& src)
	{
		ptr = new T;
		*ptr = src;
	}
	MoreUniquePtr(const MoreUniquePtr&) = delete; // copy

	// MoreUniquePtr(MoreUniquePtr&& src) // move
	// {
	// 	std::cout << "Move construction" << std::endl;
	// 	ptr = new T;
	// 	ptr = src.ptr;
	// }

	~MoreUniquePtr()
	{
		if (ptr)
			delete ptr;
	}

	// copy assignment operator
	MoreUniquePtr& operator=(const MoreUniquePtr& src) = delete; // copy assignmt

	// MoreUniquePtr& operator=(MoreUniquePtr&& src) // move assignmt
	// {
	// 	std::cout << "Move assignment" << std::endl;
	// 	if (ptr)
	// 		delete ptr;
	// 	ptr = src.ptr;
	// }

	T get()
	{
		return *ptr;
	}

private:
	T * ptr = nullptr;
};


int main(int /*argc*/, char** /*argv*/)
{
	MoreUniquePtr<int> default_constructed;

	MoreUniquePtr<int> int_constructor(8);
	assert(int_constructor.get() == 8);
	std::cout << "Got " << int_constructor.get() << std::endl;

	std::string yolo = "yolo";
	MoreUniquePtr<std::string> string_constructor(yolo);
	std::cout << "Got " << string_constructor.get() << std::endl;
	assert(std::string(string_constructor.get()) == yolo);

	const char * more_yolo = "more yolo";
	MoreUniquePtr<const char *> char_star_constructor(more_yolo);
	std::cout << "Got " << char_star_constructor.get() << std::endl;
	assert(std::string(char_star_constructor.get()) == "more yolo");

	MoreUniquePtr<double> double_constructor(3.14159);
	std::cout << "Got " << double_constructor.get() << std::endl;
	assert(double_constructor.get() == 3.14159);

	// MoreUniquePtr<int> for_move_construction(2);
	// MoreUniquePtr<int> move_constructed = std::move(for_move_construction);
	// std::cout << "Got " << move_constructed.get() << std::endl;
	// assert(move_constructed.get() == 2);
}
