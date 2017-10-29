#pragma once

#include <cstddef>
#include <memory>

namespace Mehrdad {

namespace {
template<typename R, typename... Args>
class Callable
{
public:
	Callable(R ret, Args... args);
	~Callable(){}

	R operator() (Args... args);
};
}


template<typename R, typename... Args>
class Function
{
public:
	Function();
	Function(std::nullptr_t);

	template<typename F>
	Function(F functor);

	~Function();

	explicit operator bool() const;

	R operator() (Args... args);

	Function(const Function& other) = delete;//Copy is not supported for now
	Function(Function&& other) = delete;//Move is not supported for now

private:
	std::unique_ptr<Callable<R(Args...)>> mCallable;
};
}
