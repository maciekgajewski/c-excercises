#include <iostream>
#include <stdexcept>

template<typename A, typename B>
struct Pair
{
	Pair() = default;
	Pair(const A& f, const B& s) : first(f), second(s) {}
	
	template<typename U0, typename U1>
	Pair(const Pair<U0, U1>& other) : first(other.first), second(other.second) {}
	
	A first;
	B second;
};

template<typename T0, typename T1>
Pair<T0, T1> MakePair(const T0& a, const T1& b)
{
	return Pair<T0, T1>(a, b);
}

int main()
{
	std::string s = "Hello";
	int i = 7;
	const int ci = 8;
	const int& cref = ci;
	
	Pair<int, int> pair = MakePair(7, 6.6);
	pair.first = 7;
	pair.second = 6.6;
}