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

  lhs[0][1] = 2;
  lhs[0][2] = 3;
  lhs[0][3] = 4;
  rhs[1][0] = 2;
  rhs[2][0] = 3;
  rhs[3][0] = 4;

  Matrix44 mult2 = lhs * rhs;
  BOOST_REQUIRE_EQUAL(mult2[0][0], 1+4+9+16);

  Vector3D myVec({1, 2, 3});
  Vector3D multVec = lhs * myVec;
  BOOST_REQUIRE_EQUAL(multVec[0], 1+4+9+4);
  BOOST_REQUIRE_EQUAL(multVec[1], 2);
  BOOST_REQUIRE_EQUAL(multVec[2], 3);

}

BOOST_AUTO_TEST_SUITE_END()