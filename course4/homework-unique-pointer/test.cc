#include<iostream>
#include<cstring>
#include <cassert>
#include "collectable.h"
#include "refcounted.h"

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

template<typename T, typename Arg>
void refcauntTest(Arg arg)
{
     auto c1 = course::RefcountingPointer<T>::createInstance(arg);
     auto c2 = c1;
     auto c3 = c2;
     assert(*c1 == *c3);
     assert(c1.getCount() == 3);
     auto c4 = std::move(c2);
     assert(*c4 == *c3);
     assert(c1.getCount() == 3);
     c2 = c1;
     assert(c1.getCount() == 4);
     c3 = c1;
     assert(c1.getCount() == 4);
     c2 = std::move(c4);
     assert(c1.getCount() == 3);
}

class TestEntity
{
  public:
    TestEntity(std::string& field)
    {
        this -> field = field;
    }

    bool operator ==(const TestEntity& other) const
    {
        return field == other.field;
    }

    std::string field;
};

int main()
{
    std::cout<<"Start collectable basic tests" << std::endl;
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

    std::cout<<"Start refcounting pointer basic tests" << std::endl;
    auto c4 = course::RefcountingPointer<std::string>::createInstance("TEST");
    assert(c4.get() == "TEST");
    auto c5 = course::RefcountingPointer<double>::createInstance(3.0);
    assert(*c5 == 3.0);
    auto c6 = course::RefcountingPointer<TestEntity>::createInstance(std::string("3.0"));
    assert(c6->field == "3.0");

    std::cout<<"Start refcounting tests" << std::endl;
    refcauntTest<std::string, const char *>("ABC");
    refcauntTest<int, int>(2);
    refcauntTest<TestEntity, std::string>("ABC");
}
