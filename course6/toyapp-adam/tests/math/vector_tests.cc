#include "math/vector.h"

#define BOOST_TEST_MODULE stringtest
#include <boost/test/included/unit_test.hpp>

using namespace Math;

BOOST_AUTO_TEST_SUITE(vector_tests)

BOOST_AUTO_TEST_CASE(constructor)
{
	Vector2D underTest;
	BOOST_REQUIRE(true);
}

BOOST_AUTO_TEST_SUITE_END()
