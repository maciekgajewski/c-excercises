#include <iostream>
#include <string>

void stupidWrite(char b)
{
	std::cout << int(b) << std::endl;
}



template<typename T1, typename T2>
struct Buffer
{
	char bytes[sizeof(T)];
	
	void Set(const T1& v)
	{
		T1* asT = reinterpret_cast<T1*>(bytes);
		*asT = v;
	}
	
	void Send() const
	{
		for(int i = 0; i < sizeof(T1); i++)
		{
			stupidWrite(bytes[i]);
		}
	}
};



int main()
{
	Buffer<int, double> b;
	
	b.Set(77);
	b.Send();

}