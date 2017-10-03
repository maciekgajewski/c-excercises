#include "displaylib/vector3d.h"

#include "gtest/gtest.h"

using namespace Display;

TEST(Vector3D, Test1)
{
	Vector3D v {1,2,3};

	ASSERT_EQ(v.x, 1);
	ASSERT_EQ(v.y, 2);
	ASSERT_EQ(v.z, 3);
}
