#pragma once
#include <utility>

namespace jds {

template <typename T>
class unique_ptr {
public:
	unique_ptr() = default;
	unique_ptr(unique_ptr<T> const & other) = delete;

	unique_ptr(unique_ptr<T> && other)
	{
		this->object = other.object;
		other.object = nullptr;
	}

	unique_ptr(T * object)
	{
		this->object = object;
	}

	unique_ptr<T> & operator=(unique_ptr<T> const & other) = delete;

	unique_ptr<T> & operator=(unique_ptr<T> && other)
	{
		this->object = other.object;
		other.object = nullptr;
		return *this;
	}

	~unique_ptr()
	{
		if (this->object != nullptr)
		{
			delete this->object;
			this->object = nullptr;
		}
	}

	T & operator*() { return *(this->object); }
	T * get() { return this->object; }
private:
	T * object{nullptr};
};

template <typename T, typename ...Args>
unique_ptr<T> make_unique(Args &&...args)
{
	T * object = new T(std::forward<Args>(args)...);
	return unique_ptr<T>(object);
}

}
