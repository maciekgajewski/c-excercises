#include "displaylib/vector.h"

#include "gtest/gtest.h"

using namespace Display;

TEST(Vector_double_3, Initialization)
{
	Vector3D v {1,2,3};

	ASSERT_EQ(v.x, 1);
	ASSERT_EQ(v.y, 2);
	ASSERT_EQ(v.z, 3);
}

TEST(Vector_int_2, Initialization)
{
	Pixel v {1,2};

	ASSERT_EQ(v.x, 1);
	ASSERT_EQ(v.y, 2);
}

TEST(Vector_int_3, Initialization)
{
	Vector<int, 3> v {{1,2,3}};

	ASSERT_EQ(v[0], 1);
	ASSERT_EQ(v[1], 2);
	ASSERT_EQ(v[2], 3);
}
