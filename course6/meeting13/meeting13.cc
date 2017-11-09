#include <cstddef>
#include <array>
#include <iostream>
#include <vector>

template <typename ValueT, std::size_t N>
struct fixed_vector
{
	void push_back(const ValueT& value) { _push_back(value); }
	void push_back(ValueT&& value) {  _push_back(std::move(value)); }

	std::size_t size() const { return mSize; }
	std::size_t capacity() const { return mElements.size(); }

	ValueT* begin() { return mElements.data(); }
	ValueT* end() { return mElements.data() + mSize; }

private:
	template <typename ArgT>
	void _push_back(ArgT&& value)
	{
		if (size() == capacity())
			throw std::runtime_error("full");

		mElements[mSize] = std::forward<ArgT>(value);
		++mSize;
	}

	std::size_t mSize = 0;
	std::array<ValueT, N> mElements;
};

struct A
{
	A() =default;

	A(const A& a) : mText(a.mText) { std::cout << "A copied" << std::endl; }
	A& operator=(const A& a) { mText = a.mText; std::cout << "A copy assign" << std::endl; return *this;}

	A(A&& a) : mText(std::move(a.mText)) { std::cout << "A moved" << std::endl; }
	A& operator=(A&& a) { mText = std::move(a.mText); std::cout << "A move assign" << std::endl; return *this; }
		
	std::string mText;
};

int main()
{
	fixed_vector<A, 5> vi; 

	fixed_vector<A, 5> vv; 

	std::cout << "START" << std::endl;
	vv = std::move(vi);
	std::cout << "END" << std::endl;

	A a;
	vi.push_back(std::move(a));
	vi.push_back(a);

	return 0;
}
