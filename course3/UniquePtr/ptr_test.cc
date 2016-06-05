#include "my_unique_ptr.h"
#include <array>
#include <string>
#include <cassert>
#include <iostream>
#include <cstring>
#include <memory>


struct Foo
{
    Foo()      { std::cout << "Foo::Foo\n";  }
    ~Foo()     { std::cout << "Foo::~Foo\n"; }
    void bar() { std::cout << "Foo::bar\n";  }
    int ret6() { std::cout << "Foo::ret6\n"; return 6; }
    std::array<int, 5> retArray(){
        std::array<int, 5> arr;
        for(int i=0; i<5; ++i) {
            arr[i]=i*2;
        }
    return arr;
    }
};


std::string s(const Foo &){
    std::cout << "s(const Foo&)\n";
    return "aString";
}


int main()
{
    
    std::cout << "Testing std::unique_ptr..." << std::endl;
    std::unique_ptr<Foo> std_p1(new Foo);  // p1 owns Foo
    std::unique_ptr<Foo> std_p2(std::move(std_p1));  // now p2 owns Foo
    assert(std_p1->ret6() == std_p2->ret6());
    assert( s(*std_p1) == "aString" );
    std_p1 = std::move(std_p2);  // ownership returns to p1
    std::cout << "destroying std_p2...\n";
    std::unique_ptr<Foo> std_p3;
    assert (std_p3 == nullptr);
    std_p3.swap(std_p1);
    assert (std_p1 != std_p3);
    assert (std_p3 != nullptr);
    assert (std_p1 == nullptr);
    std::array<int, 5>  std_arr = std_p1->retArray();
    std::cout << "std_arr[1]=" << std_arr[1] << std::endl;
    assert(std_arr[1] == 2);
    std::cout << "std::unique_ptr test passes" << std::endl;
    
    std::cout << " " << std::endl;
    
    std::cout << "Testing MyUniquePtr..." << std::endl;
    MyUniquePtr<Foo> my_p1(new Foo);  // p1 owns Foo
    MyUniquePtr<Foo> my_p2(std::move(my_p1));  // now p2 owns Foo
    assert(my_p1->ret6() == my_p2->ret6());
    assert( s(*my_p1) == "aString" );
    my_p1 = std::move(my_p2);  // ownership returns to p1
    std::cout << "destroying my_p2...\n";
    MyUniquePtr<Foo> my_p3;
    assert (my_p3 == nullptr);
    my_p3.swap(my_p1);
    assert (my_p1 != my_p3);
    assert (my_p3 != nullptr);
    assert (my_p1 == nullptr);
    std::array<int, 5>  my_arr = my_p1->retArray();
    std::cout << "my_arr[1]=" << my_arr[1] << std::endl;
    assert(my_arr[1] == 2);
    std::cout << "MyUniquePtr test passes" << std::endl;
    
}
