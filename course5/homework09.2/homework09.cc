#include "uniqueptr.h"

#include <string>
#include <cstring>
#include <cassert>

int main()
{
    UniquePtr<std::string> p1 = MakeUnique<std::string>("Mokus");
    assert(p1.get() != nullptr);
    assert(*p1 == "Mokus");
    assert(&(*p1) == p1.get());
    assert(strcmp(p1->c_str(), "Mokus") == 0);
    assert(p1 != nullptr);
    assert(p1 == p1);
    UniquePtr<std::string> p2 = MakeUnique<std::string>("Mokus");
    assert(p1 != p2);
    assert(*p1 == *p2);
    UniquePtr<std::string> p3;
    assert(p1 != p3);
    p2.reset();
    assert(p2 == nullptr);
    assert(p2 == p3);
    UniquePtr<std::string> p4 = MakeUnique<std::string>("Mokus");
    UniquePtr<std::string> p5 = MakeUnique<std::string>("Macska");
    assert(*p4 != *p5);
    p5 = std::move(p1);
    assert(*p4 == *p5);
    assert(p1 == nullptr);
    UniquePtr<std::string> p6 = std::move(p5);
    assert(*p4 == *p6);
    assert(p5 == nullptr);
}
