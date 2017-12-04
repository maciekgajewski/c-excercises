#include "../displaylib/vector.h"
#include "../displaylib/objects.h"

#include <cassert>
#define BOOST_TEST_MODULE objects_test
#include <boost/test/included/unit_test.hpp>

using namespace Display;

BOOST_AUTO_TEST_SUITE (camera_tests)

BOOST_AUTO_TEST_CASE (projection_tests)
{
  Vector3D input3d({3, 2, 1});
  Display::Camera cam;
  Pixel output2d = cam.project2D(input3d);
  BOOST_REQUIRE_EQUAL(output2d[0], 3);
  BOOST_REQUIRE_EQUAL(output2d[1], 2);
}

BOOST_AUTO_TEST_SUITE_END()