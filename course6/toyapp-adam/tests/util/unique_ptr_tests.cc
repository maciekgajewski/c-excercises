#include "util/unique_ptr.h"
#include <boost/test/unit_test.hpp>

using namespace Util;

namespace {
	struct TestState
	{
		bool constructed = false;
		bool destructed = false;
	};

	struct TestType
	{
		TestType(TestState& s) : state(s) { state.constructed = true; }
		~TestType() { state.destructed = true; }

		TestState& state;
	};
}

BOOST_AUTO_TEST_SUITE(UniquePtrTests)

BOOST_AUTO_TEST_CASE(Empty)
{
	TestState state;
	UniquePtr<TestType> underTest;

	BOOST_CHECK_EQUAL(underTest, nullptr);
	BOOST_CHECK_EQUAL(false, state.constructed);
	BOOST_CHECK_EQUAL(false, state.destructed);
}

BOOST_AUTO_TEST_CASE(Make)
{
	TestState state;
	auto underTest = UniquePtr<TestType>::Make(state);

	BOOST_CHECK_NE(underTest, nullptr);
	BOOST_CHECK_EQUAL(&(underTest->state), &state);
	BOOST_CHECK_EQUAL(&((*underTest).state), &state);
	BOOST_CHECK_EQUAL(true, state.constructed);
	BOOST_CHECK_EQUAL(false, state.destructed);
}

static UniquePtr<TestType> CreateTestPtr(TestState& state)
{
	return UniquePtr<TestType>::Make(state);
}

BOOST_AUTO_TEST_CASE(MoveConstructor)
{
	TestState state;
	UniquePtr<TestType> underTest(CreateTestPtr(state));

	BOOST_CHECK_NE(underTest, nullptr);
	BOOST_CHECK_EQUAL(&(underTest->state), &state);
	BOOST_CHECK_EQUAL(&((*underTest).state), &state);
	BOOST_CHECK_EQUAL(true, state.constructed);
	BOOST_CHECK_EQUAL(false, state.destructed);
}

BOOST_AUTO_TEST_CASE(MoveAssignment)
{
	TestState state;
	UniquePtr<TestType> underTest;

	BOOST_CHECK_EQUAL(underTest, nullptr);

	underTest = CreateTestPtr(state);

	BOOST_CHECK_NE(underTest, nullptr);
	BOOST_CHECK_EQUAL(&(underTest->state), &state);
	BOOST_CHECK_EQUAL(&((*underTest).state), &state);
	BOOST_CHECK_EQUAL(true, state.constructed);
	BOOST_CHECK_EQUAL(false, state.destructed);
}

BOOST_AUTO_TEST_CASE(Destructor)
{
	TestState state;
	{
		auto underTest = UniquePtr<TestType>::Make(state);
		BOOST_CHECK_EQUAL(true, state.constructed);
	}
	BOOST_CHECK_EQUAL(true, state.destructed);
}

BOOST_AUTO_TEST_SUITE_END()
