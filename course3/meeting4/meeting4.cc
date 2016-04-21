#include <iostream>
#include <memory>

struct MyType
{
    MyType() { std::cout << "def constructor" << std::endl; }
    MyType(int i) :x(i) {std::cout << "init constr, i=" << i << std::endl; }
    ~MyType() { std::cout << "destructor x=" << x << std::endl; }
    
    int x;
};

void print(std::unique_ptr<MyType> mt)
//void print(const MyType& mt)
{
    std::cout << "MyType=" << mt->x << std::endl;
}

int main()
{
    //std::unique_ptr<MyType> p(new MyType(77));
    std::unique_ptr<MyType> p = std::make_unique<MyType>(44);
    std::unique_ptr<MyType> p2 = std::move(p);
    auto local = MyType(66);
    
    print(std::make_unique<MyType>(1234));
    
    std::cout << p2->x  << std::endl;
}