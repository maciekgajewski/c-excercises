#include "../displaylib/matrix.h"
#include "../displaylib/vector.h"

#include <cassert>
#define BOOST_TEST_MODULE test_matrices
#include <boost/test/included/unit_test.hpp>

using namespace Display;

BOOST_AUTO_TEST_SUITE (matrix_tests)

BOOST_AUTO_TEST_CASE (constructor_tests)
{
  Matrix44 myMat;

  float element = myMat[0][0];
  BOOST_REQUIRE_EQUAL(element, 0);

  Matrix44 zeroMatrix;
  zeroMatrix.Zero();
  float zeroElement = zeroMatrix[0][0];
  BOOST_REQUIRE_EQUAL(zeroElement, 0);

}


BOOST_AUTO_TEST_CASE (operator_tests)
{
  Matrix44 lhs = Matrix44::Eye();
  Matrix44 rhs = Matrix44::Eye();

  Matrix44 mult = lhs * rhs;

  float element = mult[0][0];
  BOOST_REQUIRE_EQUAL(element, 1);

  lhs[0][2] = 2;
  lhs[0][3] = 3;
  lhs[0][4] = 4;
  rhs[2][0] = 2;
  rhs[3][0] = 3;
  rhs[4][0] = 4;

  Matrix44 mult2 = lhs * rhs;
  BOOST_REQUIRE_EQUAL(mult2[0][0], 1+4+9+16);

}

BOOST_AUTO_TEST_SUITE_END()