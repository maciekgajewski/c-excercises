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
  std::array row1({1, 2, 3, 4});
  std::array other_rows({0, 0, 0, 0});
  //Matrix44 lhs({row1, other_rows, other_rows, other_rows});
  //Matrix44 rhs({row1, other_rows, other_rows, other_rows});

  Matrix44 lhs({{1, 2, 3, 4}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}});
  Matrix44 rhs({{1, 2, 3, 4}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}});

  Matrix44 mult = lhs * rhs;

  float element = mult[0][0];
  BOOST_REQUIRE_EQUAL(element, 1);

}

BOOST_AUTO_TEST_SUITE_END()