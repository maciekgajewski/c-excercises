#include <iostream>
#include <memory>

struct MyType
{
    MyType() { std::cout << "def constructor" << std::endl; }
    MyType(int i) :x(i) {std::cout << "init constr, i=" << i << std::endl; }
    ~MyType() { std::cout << "destructor x=" << x << std::endl; }
    
    int x;
};

int main(int argc, char** argv)
{
    std::unique_ptr<MyType[]> p(new MyType[argc]);
    
    std::shared_ptr<MyType> sp = std::make_shared<MyType>(666);
    std::shared_ptr<MyType> sp2 = sp;
    
    p[1].x = 5;
    
}