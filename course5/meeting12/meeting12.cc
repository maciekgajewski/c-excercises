#include <iostream>

int main(int /*argc*/, char** /*argv*/)
{
	std::cout << "Hello, world!" << std::endl;
}


template<typename T>
class Outer
{
	template<typename Q>
	class Inner
	{
		int Fun();
	};
	
	template<typename It>
	void Read(It first, It last);
};

template<typename T>
template<typename Q>
int Outer<T>::Inner<Q>::Fun()
{
}

template<typename T>
template<typename It>
void Outer<T>::Read(It first, It last)
{
}



