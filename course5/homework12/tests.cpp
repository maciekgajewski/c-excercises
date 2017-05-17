#include <cassert>
#include "comparers.h"

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
    auto target1 = ColumnComparer<BasicComparer>(2, '/t', BasicComparer());
    assert (target1("1/t29", "a/t3"));
    assert (target1("/t/t14", "a/t3"));
    assert (target1("-/t", "/t99/tblaaah"));
    assert (target1("1", "a/tВасилий"));

    auto target2 = ColumnComparer<NumericComparer>(1, '/n', NumericComparer());
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
