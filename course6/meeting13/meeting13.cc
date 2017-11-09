#include <cstddef>
#include <array>
#include <iostream>
#include <vector>

template <typename ValueT, std::size_t N>
struct fixed_vector
{
	void push_back(const ValueT& value) { _push_back(value); }
	void push_back(ValueT&& value) { _push_back(std::move(value)); }

	template <typename... Args> 
	void emplace_back(Args&&... args)
	{
		if (size() == capacity())
			throw std::length_error("full");

		mElements[mSize].~ValueT();
		new (mElements.data() + mSize) ValueT(std::forward<Args>(args)...);
		++mSize;
	}

	std::size_t size() const { return mSize; }
	std::size_t capacity() const { return mElements.size(); }

	ValueT* begin() { return mElements.data(); }
	ValueT* end() { return mElements.data() + mSize; }

private:
	template <typename ArgT>
	void _push_back(ArgT&& value)
	{
		if (size() == capacity())
			throw std::length_error("full");

		mElements[mSize] = std::forward<ArgT>(value);
		++mSize;
	}

	std::size_t mSize = 0;
	std::array<ValueT, N> mElements;
};

struct A
{
	A() { std::cout << "A ctor" << std::endl; }

	explicit A(const std::string& text, int) : mText(text) { std::cout << "A ctor(string)" << std::endl; }
	~A() { std::cout << "A dtor" << std::endl; }

	A(const A& a) : mText(a.mText) { std::cout << "A copied" << std::endl; }
	A& operator=(const A& a) { mText = a.mText; std::cout << "A copy assign" << std::endl; return *this;}

	A(A&& a) : mText(std::move(a.mText)) { std::cout << "A moved" << std::endl; }
	A& operator=(A&& a) { mText = std::move(a.mText); std::cout << "A move assign" << std::endl; return *this; }
		
	std::string mText;
};

template <typename LastArg>
void foo(LastArg&& last)
{
	std::cout << last << std::endl;
}

template <typename Arg, typename... Args>
void foo(Arg&&, Args&&... args)
{
   foo(std::forward<Args>(args)...);
}

int main()
{
	fixed_vector<A, 3> vi; 

	std::cout << "START" << std::endl;
	vi.emplace_back("foo", 5);
	std::cout << "END" << std::endl;

	foo(1,2,3, "foo");

	return 0;
}









