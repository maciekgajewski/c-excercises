#pragma once

#include <utility>
#include <memory>
#include <iterator>

namespace course {

template<typename T>
struct pointer_value_pair
{
	pointer_value_pair(std::unique_ptr<pointer_value_pair<T>>&& pointer, T& value) : value(value), pointer(std::move(pointer)) {}
	
	std::unique_ptr<pointer_value_pair<T>> pointer;
    T& value;
};

template<typename T>
class linked_list_iterator : public std::iterator<std::input_iterator_tag, T, T, const T*, T> //need to derive from std::iterator to not get strange errors of missing iterator_traits
{
public:
	linked_list_iterator(pointer_value_pair<T>* pointer) : pointer(pointer) {}

	linked_list_iterator& operator++()
	{
		pointer = (pointer -> pointer).get();
		return *this;
	}

	linked_list_iterator operator++(int)
	{
		pointer_value_pair<T>* result = pointer;
		pointer = pointer -> pointer;
		return result;
	}

	T& operator*()
	{
		return pointer -> value;
	}

	bool operator!=(const linked_list_iterator& other_iter) const
	{
		return (pointer!=other_iter.pointer);
	}

	bool operator==(const linked_list_iterator& other_iter) const
	{
		return (pointer==other_iter.pointer);
	}

private:
	pointer_value_pair<T>* pointer;
};

template<typename T>
class linked_list
{
public:
	linked_list() {}
	
	bool empty() const
	{
		return !begin_ptr;
	}

	void push_front(T& insert_val)
	{
		begin_ptr = std::make_unique<pointer_value_pair<T>>(std::move(begin_ptr), insert_val);
	}

	void pop_front()
	{
		begin_ptr = std::move(begin_ptr -> pointer);
	}

	T& front()
	{
		return begin_ptr -> value;
	}
	
	linked_list_iterator<T> begin()
	{
		return begin_ptr.get();
	}

	linked_list_iterator<const T> begin() const
	{
		return begin_ptr.get();
	}

	linked_list_iterator<T> end()
	{
		return nullptr;
	}

	linked_list_iterator<const T> end() const
	{
		return nullptr;
	}

private:
	std::unique_ptr<pointer_value_pair<T>> begin_ptr;
};

}