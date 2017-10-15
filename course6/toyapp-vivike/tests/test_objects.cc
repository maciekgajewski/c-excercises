#include "../displaylib/objects.h"

#include <cassert>
#define BOOST_TEST_MODULE objects_test
#include <boost/test/included/unit_test.hpp>

using namespace Display;

BOOST_AUTO_TEST_SUITE (vector_tests)

BOOST_AUTO_TEST_CASE (constructor_tests)
{
  Vector<int, 3> myvec({3, 9, 6});
  BOOST_REQUIRE_EQUAL(myvec[0], 3);
  BOOST_REQUIRE_EQUAL(myvec[1], 9);
  BOOST_REQUIRE_EQUAL(myvec[2], 6);
}

BOOST_AUTO_TEST_CASE (operator_tests)
{
  Vector<int, 3> vec_a({3, 9, 6});
  Vector<int, 3> vec_b({1, 2, 3});

  int b = 3;

  Vector<int, 3> sumvec = vec_a + vec_b;
  BOOST_REQUIRE_EQUAL(sumvec[0], 4);
  BOOST_REQUIRE_EQUAL(sumvec[1], 11);
  BOOST_REQUIRE_EQUAL(sumvec[2], 9);

  Vector<int, 3> timesvec = vec_a * b;
  BOOST_REQUIRE_EQUAL(timesvec[0], 9);
  BOOST_REQUIRE_EQUAL(timesvec[1], 27);
  BOOST_REQUIRE_EQUAL(timesvec[2], 18);

  Vector<int, 3> diffvec1 = vec_a - vec_b;
  BOOST_REQUIRE_EQUAL(diffvec1[0], 2);
  BOOST_REQUIRE_EQUAL(diffvec1[1], 7);
  BOOST_REQUIRE_EQUAL(diffvec1[2], 3);

  Vector<int, 3> diffvec2 = vec_b - vec_a;
  BOOST_REQUIRE_EQUAL(diffvec2[0], -2);
  BOOST_REQUIRE_EQUAL(diffvec2[1], -7);
  BOOST_REQUIRE_EQUAL(diffvec2[2], -3);

  Vector<int, 3> divvec = vec_a / b;
  BOOST_REQUIRE_EQUAL(divvec[0], 1);
  BOOST_REQUIRE_EQUAL(divvec[1], 3);
  BOOST_REQUIRE_EQUAL(divvec[2], 2);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE (camera_tests)

BOOST_AUTO_TEST_CASE (propjection_tests)
{
  Vector3D input3d({3, 2, 1});
  Display::Camera cam;
  Pixel output2d = cam.project2D(input3d);
  BOOST_REQUIRE_EQUAL(output2d[0], 3);
  BOOST_REQUIRE_EQUAL(output2d[1], 2);
}

BOOST_AUTO_TEST_SUITE_END()