#include "unique_ptr.h"
#include <iostream>
#include <memory>
#include <cstring>

//template<typename template<typename T> class PtrType>
template <typename PtrType>
void test(){
	PtrType a(new char[5]);
	std::strcpy(a.get(),"abcd");
	std::cout << "value of a=" << a.get() <<std::endl;	
}

int main(){
	std::cout<<"test std::unique_ptr"<<std::endl;
	test<std::unique_ptr<char[]>>();
	std::cout<<std::endl;
	std::cout<<"test MyUniquePtr"<<std::endl;
	test<MyUniquePtr<char[]>>();
};
