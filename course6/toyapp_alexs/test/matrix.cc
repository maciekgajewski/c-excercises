#include "displaylib/matrix.h"

#include "gtest/gtest.h"

using namespace Display;

TEST(Matrix_2x2, Multiplication)
{
	Matrix<2, 2, int> matrix1
	{
		1, 2,
		3, 4
	};

	Matrix<2, 2, int> matrix2
	{
		1, 2,
		3, 4
	};

	auto result = matrix1 * matrix2;

	ASSERT_EQ(result[0][0], 7);
	ASSERT_EQ(result[0][1], 10);
	ASSERT_EQ(result[1][0], 15);
	ASSERT_EQ(result[1][1], 22);
}
