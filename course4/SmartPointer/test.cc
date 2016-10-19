#include "smart.hh"

#include <cassert>
#include <iostream>
#include <memory>

struct Foo { // object to manage
    Foo() { std::cout << "Foo ctor\n"; }
    Foo(const Foo&) { std::cout << "Foo copy ctor\n"; }
    Foo(Foo&&) { std::cout << "Foo move ctor\n"; }
    ~Foo() { std::cout << "~Foo dtor\n"; }
    void Bla()
    {std::cout<<"bla"<<std::endl;}

};

template<typename UP>
void test()
{
     std::cout << "test constructor (1)...\n";
     UP up1;  // up1 is empty
     UP up1b(nullptr);  // up1b is empty

     std::cout << "test constructor (2)...\n";
     {
         UP up2(new Foo); //up2 now owns a Foo
     } // Foo deleted

     std::cout << "test move...\n";
     {
        UP up5a(new Foo);
        UP up5b(std::move(up5a)); // ownership transfer
     }


     std::cout << "test operators...\n";
     {
        UP upEq(new Foo);
        //UP<Foo> upEqa = upEq;
        upEq->Bla();

        auto b = upEq.get();
        b->Bla();

        auto aCopy = *upEq;
        aCopy.Bla();
     }
}

int main()
{
    std::cout << "Testing course::uniquePtr..." << std::endl;
    test<std::unique_ptr<Foo>>();
    std::cout << "course::uniquePtr passes" << std::endl;

    std::cout << "Testing course::uniquePtr..." << std::endl;
    test<course::uniquePtr<Foo>>();
    std::cout << "course::uniquePtr passes" << std::endl;
}
