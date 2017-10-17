#include "../displaylib/matrix.h"
#include "../displaylib/vector.h"

#include <cassert>
#define BOOST_TEST_MODULE test_matrices
#include <boost/test/included/unit_test.hpp>

using namespace Display;

BOOST_AUTO_TEST_SUITE (matrix_tests)

BOOST_AUTO_TEST_CASE (constructor_tests)
{
  Matrix<int, 1, 1> myMat;
  int element = myMat[MatrixElement({0, 0})];
  BOOST_REQUIRE_EQUAL(element, 0);

  Matrix<float, 1, 1> myMat2 = myMat.Zeroes();
  int element2 = myMat2[MatrixElement({0, 0})];
  BOOST_REQUIRE_EQUAL(element2, 0);
}

BOOST_AUTO_TEST_SUITE_END()