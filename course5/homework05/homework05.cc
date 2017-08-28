#include <cstdlib>
#include <iostream>
#include <cassert>
#include <sstream>
#include <cmath>
#include "vector2d.h"

using namespace homework05;

void test_equals()
{
    const auto v1 = Vector2D(1, 0);
    const auto v2 = Vector2D(1, 0);

    assert (v1 == v2);
}

void test_not_equals()
{
    auto v1 = Vector2D(1, 0);
    auto v2 = Vector2D(1, 0);

    assert ((v1 != v2) == false);

    v1 = Vector2D(2, 0);

    assert (v1 != v2);
}

void test_plus()
{
    const auto v1 = Vector2D(10.0, 11.0);
    const auto v2 = Vector2D(1, -2);

    assert(v1 + v2 == Vector2D(11, 9));
}

void test_minus()
{
    auto v1 = Vector2D(7.0, -9);
    auto v2 = Vector2D(3, -4);
    assert(v1 - v2 == Vector2D(4, -5));
}

void test_unary_minus()
{
    auto v1 = Vector2D(4, 0);
    assert (-v1 == Vector2D(-4, 0));
    auto v2 = Vector2D(5, 7);
    assert (-v2 == Vector2D(-5, -7));
}

void test_plus_equals()
{
    auto v1 = Vector2D(7, 7);
    v1 += Vector2D(1, -1);
    assert (v1 == Vector2D(8, 6));
}

void test_minus_equals()
{
    auto v1 = Vector2D(7, 7);
    v1 -= Vector2D(1, -1);
    assert (v1 == Vector2D(6, 8));
}


void test_literal_operator()
{
    auto v = 10.0_x - 7.78_y;
    assert (v == Vector2D(10, -7.78));
}

void test_ostream()
{
    auto v = Vector2D(19, 81);
    std::stringstream out;
    out << v;
    assert (out.str() == "(19, 81)");
}

void test_from_polar()
{
    auto e = 1.78_phi;
    auto v = 10 * e;
    auto test = Vector2D(10*std::cos(1.78), 10*std::sin(1.78));
    assert(v.GetX() - test.GetX() < 0.000001 && v.GetY() - test.GetY() < 0.000001);
}

int main(int, char**)
{
    test_equals();
    test_not_equals();
    test_literal_operator();
    test_minus();
    test_minus_equals();
    test_ostream();
    test_plus();
    test_plus_equals();
    test_unary_minus();
    test_from_polar();
}


