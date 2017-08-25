#include "unique_ptr.h"
#include <cassert>
#include <string>
#include <cstring>

class TestItem
{
public:
    TestItem()
    {}

    TestItem(const std::string& str) : field(str)
    {}

    TestItem(std::string && str) : field(std::move(str))
    {}

    TestItem(const TestItem& item) : field(item.field)
    {}

    TestItem(TestItem && item)
    {
        field = std::move(item.field);
        item.field = std::string();
    }

    const char* GetCStr() const
    {
        return this->field.c_str();
    }

    bool operator == (const TestItem& other) const
    {
        return this->field == other.field;
    }

private:
    std::string field;
};

void test_unique_ptr_get()
{
    TestItem * p = new TestItem("blaah");
    auto myPtr = UniquePtr<TestItem>(p);
    assert(myPtr.get() == p);
}

void test_unique_ptr_release()
{
    TestItem * p = new TestItem("blaah");
    auto myPtr = UniquePtr<TestItem>(p);
    auto t = myPtr.release();
    assert(t == p);
    assert(myPtr.get() == nullptr);
    delete p;
}

void test_unique_ptr_reset()
{
    TestItem * p = new TestItem("blaah");
    auto myPtr = UniquePtr<TestItem>(p);
    myPtr.reset();
    assert(myPtr.get() == nullptr);
    p = new TestItem("test");
    myPtr.reset(p);
    assert(myPtr.get() == p);
}

void test_unique_ptr_swap()
{
    TestItem * p1, * p2;
    p1 = new TestItem("blaaah");
    p2 = new TestItem("test");

    auto myPtr1 = UniquePtr<TestItem>(p1);
    auto myPtr2 = UniquePtr<TestItem>(p2);

    myPtr1.swap(myPtr2);
    assert(myPtr1.get() == p2);
    assert(myPtr2.get() == p1);

    myPtr1.reset();
    myPtr2.swap(myPtr1);
    assert(myPtr2.get() == p2);
    assert(myPtr1.get() == nullptr);

    myPtr2.reset();
    myPtr2.swap(myPtr1);
    assert(myPtr2.get() == nullptr);
    assert(myPtr1.get() == nullptr);
}

void test_unique_ptr_bool()
{
    TestItem * p = new TestItem("blaah");
    auto myPtr = UniquePtr<TestItem>(p);
    assert(myPtr);
    myPtr.reset();
    assert(!myPtr);
}

void test_unique_ptr_move()
{
    TestItem * p1, * p2;
    p1 = new TestItem("blaaah");
    p2 = new TestItem("test");

    auto myPtr1 = UniquePtr<TestItem>(p1);
    auto myPtr2 = UniquePtr<TestItem>(p2);

    myPtr2 = std::move(myPtr1);
    assert(myPtr2.get() == p2);
    assert(!myPtr1);
}

void test_unique_ptr_equals()
{
    TestItem * p1;
    p1 = new TestItem("blaaah");

    auto myPtr1 = UniquePtr<TestItem>(p1);
    auto myPtr2 = UniquePtr<TestItem>(p1);

    assert(myPtr1 == myPtr2);

    //avoid double delete
    auto t = myPtr2.release();

    myPtr1.reset();
    assert(myPtr1 != myPtr2);

}

void test_unique_ptr_minus_gt()
{
    TestItem * p = new TestItem("blaah");
    auto myPtr = UniquePtr<TestItem>(p);
    assert(std::strcmp(myPtr->GetCStr(), "blaaah") == 0);

}

void test_make_unique_no_args()
{
    auto myPtr = MakeUnique<TestItem>();
    assert(myPtr);
    assert(std::strcmp(myPtr->GetCStr(), "") == 0);
}

void test_make_unique_string_arg()
{
    auto myPtr = MakeUnique<TestItem>(std::string("blaah"));
    assert(myPtr);
    assert(std::strcmp(myPtr->GetCStr(), "blaah") == 0);
}

void test_make_unique_copy()
{
    std::string s1 = "blaah";
    std::string s2 = std::string(s1);

    //check that string is copied
    assert(s1.c_str() != s2.c_str());
    assert(std::strcmp(s1.c_str(), s2.c_str()) == 0);

    auto toCopy = TestItem(s1);
    auto myPtr = MakeUnique<TestItem>(toCopy);

    assert(myPtr);
    assert(toCopy.GetCStr() != myPtr->GetCStr());
    assert(std::strcmp(toCopy.GetCStr(),myPtr->GetCStr()) == 0);
}

void test_make_unique_move()
{
    std::string s = "blaah";
    auto p = s.c_str();
    auto test = TestItem(std::move(s));
    assert(p == test.GetCStr());

    auto myPtr = MakeUnique<TestItem>(std::move(test));
    assert(p == myPtr->GetCStr());
}

int main(int, char**)
{
    test_unique_ptr_release();
    test_unique_ptr_bool();
    test_unique_ptr_equals();
    test_unique_ptr_get();
    test_unique_ptr_minus_gt();
    test_unique_ptr_move();
    test_unique_ptr_reset();
    test_unique_ptr_swap();

    test_make_unique_copy();
    test_make_unique_move();
    test_make_unique_no_args();
    test_make_unique_string_arg();
    return 0;
}
