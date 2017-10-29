#pragma once

#include <cstddef>
#include <memory>

namespace Mehrdad {

namespace {
template<typename R, typename... Args>
class Callable
{
public:
	Callable(R ret, Args... args){}
	~Callable(){}

	R operator() (Args... args)
	{
	}
};
}


template<typename R, typename... Args>
class Function
{
public:
	Function() {}
	Function(std::nullptr_t) {}
	~Function() {}
	explicit operator bool() const { return (bool)mCallable; }

	Function(const Function& other) = delete;//Copy is not supported for now
	Function(Function&& other) = delete;//Move is not supported for now

	template<typename F>
	Function(F functor);

	R operator() (Args... args)
	{
		if (!mCallable)
			throw std::runtime_error("Calling empty function");
	}


private:
	std::unique_ptr<Callable<R, Args...>> mCallable;
};
}
