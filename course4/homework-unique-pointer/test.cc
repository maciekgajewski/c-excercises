#include<iostream>
#include<cstring>
#include <cassert>
#include "collectable.h"

template<typename T, typename Arg>
void innerCall(Arg arg1, Arg arg2)
{
    auto c1 = course::CollectablePointer<T>::createInstance(arg1);
    auto c2 = course::CollectablePointer<T>::createInstance(arg2);
    auto c3 = c1;
    auto c4 = std::move(c2);
    assert(course::CollectablePointer<T>::itemsToCollectCount() == 0);
}

template<typename T, typename Arg>
void test(Arg arg1, Arg arg2)
{
    innerCall<T, Arg>(arg1, arg2);

    assert(course::CollectablePointer<T>::itemsToCollectCount() == 3);
    course::CollectablePointer<T>::collect();
    assert(course::CollectablePointer<T>::itemsToCollectCount() == 0);
}

class TestEntity
{
  public:
    TestEntity(std::string& field)
    {
        this -> field = field;
    }

    std::string field;
};

int main()
{
    auto c1 = course::CollectablePointer<std::string>::createInstance("TEST");
    assert(c1.get() == "TEST");
    auto c2 = course::CollectablePointer<double>::createInstance(3.0);
    assert(*c2 == 3.0);
    auto c3 = course::CollectablePointer<TestEntity>::createInstance(std::string("3.0"));
    assert(c3->field == "3.0");

    std::cout<<"Start garbage collecting tests" << std::endl;
    test<std::string, const char *>("ABC", "CDE");
    test<int, int>(2, 3);
    test<TestEntity, std::string>("ABC", "XYZ");
}
