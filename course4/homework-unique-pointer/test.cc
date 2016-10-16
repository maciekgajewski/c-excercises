#include<iostream>
#include<cstring>
#include <cassert>
#include "collectable.h"

template<typename T, typename Arg>
void innerCall(Arg arg1, Arg arg2)
{
    auto c1 = course::CollectablePointer<T>::createInstance(arg1);
    std::cout << "Done 1" << std::endl;
    auto c2 = course::CollectablePointer<T>::createInstance(arg2);
    std::cout << "Done 2" << std::endl;
    auto c3 = c1;
    std::cout << "Done 3" << std::endl;
    auto c4 = std::move(c2);
    std::cout << "Done 4" << std::endl;
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

int main()
{
    auto c1 = course::CollectablePointer<std::string>::createInstance("TEST");
    assert(c1.get() == "TEST");

    std::cout<<"Start refcount tests" << std::endl;
    test<std::string, const char *>("ABC", "CDE");
    test<int, int>(2, 3);
}
