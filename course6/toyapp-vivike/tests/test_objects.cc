#include "../displaylib/objects.h"

#include <cassert>
#define BOOST_TEST_MODULE objects_test
#include <boost/test/included/unit_test.hpp>

using namespace Display;

BOOST_AUTO_TEST_SUITE (vector_tests)

BOOST_AUTO_TEST_CASE (constructor_tests)
{
  Vector<int, 3> myvec{1, 2, 3};
  BOOST_REQUIRE(myvec.vec[0] == 1);
  BOOST_REQUIRE(myvec.vec[1] == 2);
  BOOST_REQUIRE(myvec.vec[2] == 3);
}

BOOST_AUTO_TEST_CASE (operator_tests)
{
  Vector<int, 3> vec_a{1, 2, 3};
  Vector<int, 3> vec_b{1, 2, 3};

  Vector<int, 3> sumvec = vec_a + vec_b;
  BOOST_REQUIRE(sumvec.vec[0] == 2);
  BOOST_REQUIRE(sumvec.vec[1] == 4);
  BOOST_REQUIRE(sumvec.vec[2] == 6);
}

BOOST_AUTO_TEST_SUITE_END()