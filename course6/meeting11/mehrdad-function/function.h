#pragma once

#include <cstddef>
#include <memory>
#include <functional>

namespace Mehrdad {

template<typename>
class Function; //Intentionally left undefined

template<typename R, typename... Args>
class Function<R(Args...)>
{
public:
	Function() {}
	Function(std::nullptr_t) {}
	~Function() {}
	explicit operator bool() const { return static_cast<bool>(mCallable); }

	Function(const Function& other) = delete;
	Function(Function&& other) = delete;

	template<typename F>
	Function(F functor)
	{
		mCallable = std::make_unique<Callable<F>>(functor);
	}

	R operator() (Args... args)
	{
		if (!mCallable)
			throw std::runtime_error("Calling empty function");

		mCallable->Invoke(args...);
	}


private:
	struct BaseCallable
	{
		virtual ~BaseCallable() = default;
		virtual R Invoke(Args...) = 0;
	};

	template<typename F>
	struct Callable : BaseCallable
	{
		Callable(const F& f) : mF(f) {}

		R Invoke(Args... args) override
		{
			return mF(args...);
		}

	private:
		F mF;
	};

	std::unique_ptr<BaseCallable> mCallable;
};
}
