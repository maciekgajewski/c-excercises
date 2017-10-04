#include "math/vector.h"

#define BOOST_TEST_MODULE VectorTests
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

// the boost one is just inconvenient...
#define APPROX_EQUAL(a, b) BOOST_CHECK_CLOSE(a, b, 0.001)

namespace {
	using TestVector1D = Math::Vector<float, 1>;
	using TestVector2D = Math::Vector<float, 2>;
	using TestVector3D = Math::Vector<double, 3>;
}

BOOST_AUTO_TEST_SUITE(VectorTests)

BOOST_AUTO_TEST_CASE(Empty)
{
	TestVector2D underTest;
	APPROX_EQUAL(underTest[0], 0.0f);
	APPROX_EQUAL(underTest[1], 0.0f);
	APPROX_EQUAL(underTest.Length(), 0.0f);
	APPROX_EQUAL(underTest.Normalized().Length(), 1.0f);
}

BOOST_AUTO_TEST_CASE(ConstAccessOperator)
{
	const TestVector2D underTest(3.0f, 4.0f);
	auto x = underTest[0];
	auto y = underTest[1];
	APPROX_EQUAL(x, 3.0f);
	APPROX_EQUAL(y, 4.0f);
}

BOOST_AUTO_TEST_CASE(AccessOperator)
{
	TestVector2D underTest(3.0f, 4.0f);
	underTest[0] = underTest[1];
	APPROX_EQUAL(underTest[0], 4.0f);
	APPROX_EQUAL(underTest[0], 4.0f);
}

BOOST_AUTO_TEST_CASE(AssignmentAndEquality)
{
	TestVector2D v1(3.14f, 4.0f);
	TestVector2D v2(5.0f, 6.66f);
	BOOST_REQUIRE(v1 != v2);
	BOOST_CHECK_EQUAL(v1 == v2, false);
	v1 = v2;
	BOOST_REQUIRE(v1 == v2);
	BOOST_CHECK_EQUAL(v1 != v2, false);
	APPROX_EQUAL(v1[0], v2[0]);
	APPROX_EQUAL(v1[1], v2[1]);
}

BOOST_AUTO_TEST_CASE(CopyConstructor)
{
	TestVector2D v1(3.14f, 4.0f);
	TestVector2D v2(v1);
	BOOST_REQUIRE(v1 == v2);
}

BOOST_AUTO_TEST_CASE(CastToSmallerVectorType)
{
	TestVector2D v1(3.14f, 4.0f);
	TestVector1D v1d = v1;
	APPROX_EQUAL(v1d[0], 3.14f);

	TestVector2D v2(v1d, 16.5f);
	APPROX_EQUAL(v2[0], 3.14f);
	APPROX_EQUAL(v2[1], 16.5f);
}

BOOST_AUTO_TEST_CASE(OperatorPlusEquals)
{
	TestVector2D v1(3.14f, 4.0f);
	TestVector2D v2(5.0f, 6.66f);

	v1 += v2;
	APPROX_EQUAL(v1[0], 8.14f);
	APPROX_EQUAL(v1[1], 10.66f);
}

BOOST_AUTO_TEST_CASE(OperatorMinusEquals)
{
	TestVector2D v1(3.14f, 4.0f);
	TestVector2D v2(5.0f, 6.66f);

	v1 -= v2;
	APPROX_EQUAL(v1[0], -1.86f);
	APPROX_EQUAL(v1[1], -2.66f);
}

BOOST_AUTO_TEST_CASE(OperatorTimesEquals)
{
	TestVector2D v1(3.14f, 4.0f);

	v1 *= 3.0f;
	APPROX_EQUAL(v1[0], 9.42f);
	APPROX_EQUAL(v1[1], 12.0f);
}

BOOST_AUTO_TEST_CASE(OperatorNegate)
{
	TestVector2D underTest(31.4f, -44.1f);
	BOOST_CHECK_EQUAL(-underTest, TestVector2D(-31.4f, 44.1f));
}

BOOST_AUTO_TEST_CASE(OperatorAdd)
{
	TestVector2D v1(3.14f, 4.0f);
	TestVector2D v2(5.0f, 6.66f);
	BOOST_CHECK_EQUAL(v1 + v2, TestVector2D(8.14f, 10.66f));
}

BOOST_AUTO_TEST_CASE(OperatorSubtract)
{
	TestVector2D v1(3.14f, 4.0f);
	TestVector2D v2(5.0f, 6.66f);
	BOOST_CHECK_EQUAL(v1 - v2, TestVector2D(-1.86f, -2.66f));
}

BOOST_AUTO_TEST_CASE(Length)
{
	TestVector2D underTest(3.0f, 4.0f);
	APPROX_EQUAL(underTest.Length(), 5.0f);
}

BOOST_AUTO_TEST_CASE(Normalized)
{
	auto underTest = TestVector2D(3.0f, 4.0f).Normalized();
	APPROX_EQUAL(underTest[0], 3.0f / 5.0f);
	APPROX_EQUAL(underTest[1], 4.0f / 5.0f);
	APPROX_EQUAL(underTest.Length(), 1.0f);
}

BOOST_AUTO_TEST_CASE(DotProduct)
{
	TestVector2D v1(3.14f, 4.0f);
	TestVector2D v2(5.0f, 6.66f);
	APPROX_EQUAL(v1.Dot(v1), 25.8596f);
	APPROX_EQUAL(v1.Dot(v2), 42.34f);
}

BOOST_AUTO_TEST_CASE(CrossProduct)
{
	TestVector3D v1(-1.0, 7.0, 4.0);
	TestVector3D v2(-5.0, 8.0, 4.0);
	BOOST_CHECK_EQUAL(Math::Cross(v1, v1), TestVector3D(0.0, 0.0, 0.0));
	BOOST_CHECK_EQUAL(Math::Cross(v1, v2), TestVector3D(-4.0, -16.0, 27.0));
}

BOOST_AUTO_TEST_SUITE_END()
