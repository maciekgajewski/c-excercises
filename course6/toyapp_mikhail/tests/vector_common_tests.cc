#include "displaylib/vector_common.h"

#include <gtest/gtest.h>

using namespace Display;

TEST(Vector2DTests, InitializationList)
{
	Vector2D v{ 2.6, -3.7 };

	ASSERT_EQ(v.x(), 2.6);
	ASSERT_EQ(v.y(), -3.7);
}

TEST(Vector3DTests, InitializationList)
{
	Vector3D v{ 1.5, 2.6, 3.7 };

	ASSERT_EQ(v.x(), 1.5);
	ASSERT_EQ(v.y(), 2.6);
	ASSERT_EQ(v.z(), 3.7);
}
