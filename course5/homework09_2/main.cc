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

	MoreUniquePtr(MoreUniquePtr&& src) // move
	{
		ptr = src.ptr;
		src.ptr = nullptr;
	}

	~MoreUniquePtr()
	{
		if (ptr)
			delete ptr;
	}

	MoreUniquePtr& operator=(const MoreUniquePtr& src) = delete; // copy assignmt

	MoreUniquePtr& operator=(MoreUniquePtr&& src) // move assignmt
	{
		if (ptr)
			delete ptr;
		ptr = src.ptr;
		src.ptr = nullptr;
		return *this;
	}

	T get()
	{
		return *ptr;
	}

private:
	T * ptr = nullptr;
};


int main(int /*argc*/, char** /*argv*/)
{
	/* Test construction/destruction & get method */

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
	assert(std::string(char_star_constructor.get()) == more_yolo);

	MoreUniquePtr<double> double_constructor(3.14159);
	std::cout << "Got " << double_constructor.get() << std::endl;
	assert(double_constructor.get() == 3.14159);


	/* Test move assignment between same types */

	MoreUniquePtr<int> for_move_construction(2);
	MoreUniquePtr<int> move_constructed = std::move(for_move_construction);
	std::cout << "Got " << move_constructed.get() << std::endl;
	assert(move_constructed.get() == 2);

	MoreUniquePtr<int> for_move_assignment(3);
	MoreUniquePtr<int> move_assigned(5);
	move_assigned = std::move(for_move_assignment);
	std::cout << "Got " << move_assigned.get() << std::endl;
	assert(move_assigned.get() == 3);

	/* Test move assignment between types -- shouldn't compile */
	// MoreUniquePtr<const char *> for_move_construction_combatible_type(more_yolo);
	// MoreUniquePtr<std::string> move_constructed_combatible_type = std::move(for_move_construction_combatible_type);
	// std::cout << "Got " << move_constructed_combatible_type.get() << std::endl;
	// assert(std::string(move_constructed_combatible_type.get()) == more_yolo);
	//
	// MoreUniquePtr<const char *> for_move_assignment_combatible_type(more_yolo);
	// MoreUniquePtr<std::string> move_assigned_combatible_type(yolo);
	// move_assigned_combatible_type = std::move(for_move_assignment_combatible_type);
	// std::cout << "Got " << move_assigned_combatible_type.get() << std::endl;
	// assert(std::string(move_assigned_combatible_type.get()) == more_yolo);
	//
	// MoreUniquePtr<std::string> for_move_construction_other_type(yolo);
	// MoreUniquePtr<double> move_constructed_other_type = std::move(for_move_construction_other_type);
	// std::cout << "Got " << move_constructed_other_type.get() << std::endl;
	// assert(std::string(move_constructed_other_type.get()) == yolo);
	//
	// MoreUniquePtr<std::string> for_move_assignment_other_type(yolo);
	// MoreUniquePtr<double> move_assigned_other_type(3.86196357865);
	// move_assigned_other_type = std::move(for_move_assignment_other_type);
	// std::cout << "Got " << move_assigned_other_type.get() << std::endl;
	// assert(std::string(move_assigned_other_type.get()) == yolo);

}
