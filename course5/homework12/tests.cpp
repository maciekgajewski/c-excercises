#include <cassert>
#include "comparers.h"
#include <memory>
#include <string>

using namespace homework12;

void NumericComparerTest()
{
    auto target = NumericComparer();
    assert(target("", "10"));
    assert(!target("12", "10"));
    assert(target("9.999999", "10"));
    assert(target("-1.98", "20"));
    assert(target("2", "11"));
}

void ColumnComparerTest()
{
    std::unique_ptr<AComparer> basic_comparer = std::make_unique<BasicComparer>();
    ColumnComparer target1(2, '/t', basic_comparer);
    assert (target1("1/t29", "a/t3"));
    assert (target1("/t/t14", "a/t3"));
    assert (target1("-/t", "/t99/tblaaah"));
    assert (target1("1", "a/tВасилий"));

    std::unique_ptr<AComparer> numeric_comparer = std::make_unique<NumericComparer>();
    ColumnComparer target2(1, '/n', numeric_comparer);
    assert (!target2("12190.99", "99"));
    assert (!target2("15", "-90"));
    assert (target2("-0999", "8"));
}

int main(int, char**)
{
    NumericComparerTest();
    ColumnComparerTest();

    return 0;
}
