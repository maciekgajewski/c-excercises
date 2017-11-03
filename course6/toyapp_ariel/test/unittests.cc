#include <displaylib/vector.h>
#include <algorithm>

#define BOOST_TEST_MODULE vector_test
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (vector_test)

constexpr int size = 10;
using vector_type = int;

BOOST_AUTO_TEST_CASE (vector_type_vector_initialization)
{
    Vector<vector_type, 3> v1(1);
    Vector<vector_type, 3> v2({1, 2, 3});

    BOOST_ASSERT(v1[0] == 1);
    BOOST_ASSERT(v1[1] == 1);
    BOOST_ASSERT(v1[2] == 1);

    BOOST_ASSERT(v2[0] == 1);
    BOOST_ASSERT(v2[1] == 2);
    BOOST_ASSERT(v2[2] == 3);
}

BOOST_AUTO_TEST_CASE (vector_type_vector_dot)
{

    Vector<vector_type, size> v1(1);
    Vector<vector_type, size> v2(2);
    for(vector_type i = 0; i < size;) v2[i] = ++i;

    BOOST_ASSERT(v1.Dot(v2) == (size * (size + 1)) / 2);
}

BOOST_AUTO_TEST_CASE (vector_type_vector_minus)
{
    Vector<vector_type, size> v1(1);
    Vector<vector_type, size> v2(2);
    for(vector_type i = 0; i < size;) v2[i] = ++i;

    Vector<vector_type, size> v3 = v2 - v1;

    for(vector_type i = 0; i < size; i++)
    {
        BOOST_ASSERT(v3[i] == i);
    }
}

BOOST_AUTO_TEST_CASE (vector_type_vector_multiplication)
{
    Vector<vector_type, size> v1(2);
    for(vector_type i = 0; i < size;) v1[i] = ++i;

    Vector<vector_type, size> v3 = v1 * 2;

    for(vector_type i = 0; i < size; i++)
    {
        BOOST_ASSERT(v3[i] == (i + 1) * 2);
    }
}

BOOST_AUTO_TEST_CASE (vector_type_vector_division)
{
    Vector<vector_type, size> v1(2);
    for(vector_type i = 0; i < size;) v1[i] = ++i;

    Vector<vector_type, size> v3 = v1 / 2;

    for(vector_type i = 0; i < size; i++)
    {
        BOOST_ASSERT(v3[i] == (i + 1) / 2);
    }
}

BOOST_AUTO_TEST_CASE (vector_type_vector_length)
{
    Vector<vector_type, 3> v1({0, 1, 0});

    BOOST_ASSERT(v1.Length() == 1);
}

BOOST_AUTO_TEST_SUITE_END()
