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
	Vector<int, 3> v {1,2,3};

	ASSERT_EQ(v[0], 1);
	ASSERT_EQ(v[1], 2);
	ASSERT_EQ(v[2], 3);
}

TEST(Vector_int_3, Assignment)
{
	Vector<int, 3> v;

	v = {5,6,7};

	ASSERT_EQ(v[0], 5);
	ASSERT_EQ(v[1], 6);
	ASSERT_EQ(v[2], 7);
}

TEST(Pixel, Assignment)
{
	Pixel v;

	v = {5,6};

	ASSERT_EQ(v.x, 5);
	ASSERT_EQ(v.y, 6);
}

TEST(Vector3D, Assignment)
{
	Vector3D v;

	v = {5,6,7};

	ASSERT_EQ(v.x, 5);
	ASSERT_EQ(v.y, 6);
	ASSERT_EQ(v.z, 7);
}

TEST(Vector3D, SubscriptAndFields)
{
	Vector3D v;

	v[0] = 5;
	v[1] = 6;
	v[2] = 7;

	ASSERT_EQ(v.x, 5);
	ASSERT_EQ(v.y, 6);
	ASSERT_EQ(v.z, 7);
}

TEST(Pixel, SubscriptAndFields)
{
	Pixel v;

	v.x = 5;
	v.y = 6;

	ASSERT_EQ(v[0], 5);
	ASSERT_EQ(v[1], 6);
}
