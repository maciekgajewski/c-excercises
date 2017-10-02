#include "str/str.h"

#include <string>
#include <cassert>
#define BOOST_TEST_MODULE stringtest
#include <boost/test/included/unit_test.hpp>

using namespace mstr;

BOOST_AUTO_TEST_SUITE (stringtest)

BOOST_AUTO_TEST_CASE (constructor_tests)
{
  std::string s1 = "123";
  Str t1 = "123";
  BOOST_REQUIRE(s1.size() == t1.size());
  BOOST_REQUIRE(std::strcmp(s1.c_str(), t1.c_str()) == 0);

  std::string s2("123");
  Str t2("123");
  BOOST_REQUIRE(s2.size() == t2.size());
  BOOST_REQUIRE(std::strcmp(s2.c_str(), t2.c_str()) == 0);

  std::string s3 = s2;
  Str t3 = t2;
  BOOST_REQUIRE(s3.size() == t3.size());
  BOOST_REQUIRE(std::strcmp(s3.c_str(), t3.c_str()) == 0);
}

BOOST_AUTO_TEST_CASE (assignment_tests)
{
  std::string s1;
  Str t1;

  s1 = "123";
  t1 = "123";

  BOOST_REQUIRE(s1.size() == t1.size());
  BOOST_REQUIRE(std::strcmp(s1.c_str(), t1.c_str()) == 0);

  s1 = std::string("123");
  t1 = Str("123");

  BOOST_REQUIRE(s1.size() == t1.size());
  BOOST_REQUIRE(std::strcmp(s1.c_str(), t1.c_str()) == 0);
}

BOOST_AUTO_TEST_CASE (index_tests)
{
  std::string s1 = "123";
  Str t1 = "123";

  BOOST_REQUIRE(s1[0] == t1[0]);

  const std::string s2 = "123";
  const Str t2 = "123";

  BOOST_REQUIRE(s2[0] == t2[0]);
}

BOOST_AUTO_TEST_CASE (operator_tests)
{
  std::string s1 = "123";
  std::string s2 = "456";
  Str t1 = "123";
  Str t2 = "456";

  BOOST_REQUIRE(std::strcmp((s1 + s2).c_str(), (t1 + t2).c_str()) == 0);

  s1 += s2;
  t1 += t2;

  BOOST_REQUIRE(std::strcmp(s1.c_str(), t1.c_str()) == 0);
}

BOOST_AUTO_TEST_SUITE_END()
