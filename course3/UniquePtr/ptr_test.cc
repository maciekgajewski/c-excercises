#include "my_unique_ptr.h"
#include <array>
#include <string>
#include <cassert>
#include <iostream>
#include <memory>


struct Foo
{
    Foo()      { std::cout << "Foo::Foo\n";  }
    ~Foo()     { std::cout << "Foo::~Foo\n"; }
    std::string SayWhat(){ return "SayWhat!"; }
    int local_i;
};


int main()
{
    
    std::cout << "Testing std::unique_ptr..." << std::endl;
    std::unique_ptr<Foo> std_p1(new Foo); 
    assert( std_p1->SayWhat() == "SayWhat!" );
    std::unique_ptr<Foo> std_p2(std::move(std_p1)); 
    assert(std_p1 != std_p2 ); // p1 & p2 don't point to same object
    std::unique_ptr<int[]> std_p3(new int[1]);
    std_p3[0] = 14;
    assert(std_p3[0] == 14);
    std::unique_ptr<int> std_int(new int{7});
    assert( *(std_int.get()) == 7);//deference the ptr address returned by get
    std::cout << "std::unique_ptr test passes" << std::endl;    
    
    std::cout << "Testing MyUniquePtr..." << std::endl;
    MyUniquePtr<Foo> my_p1(new Foo); 
    assert( my_p1->SayWhat() == "SayWhat!" );
    MyUniquePtr<Foo> my_p2(std::move(my_p1)); 
    assert(my_p1 != my_p2 ); // p1 & p2 don't point to same object
    MyUniquePtr<int[]> my_p3(new int[1]);
    my_p3[0] = 14;
    assert(my_p3[0] == 14);// test of [] operator
    MyUniquePtr<int> my_int(new int{7});
    assert( *(my_int.get()) == 7);//deference the ptr address returned by get
    std::cout << "MyUniquePtr test passes" << std::endl;    
}
