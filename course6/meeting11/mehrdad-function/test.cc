#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()

#include "function.h"
#include "catch.hpp"

#include <string>

TEST_CASE("Empty functions") {
	Mehrdad::Function<int(double)> f1;
	Mehrdad::Function<double(int)> f2(nullptr);

	REQUIRE( static_cast<bool>(f1) == false );
	REQUIRE( static_cast<bool>(f2) == false );

	REQUIRE_THROWS_AS(f1(1.0), std::runtime_error);
	REQUIRE_THROWS_AS(f2(1), std::runtime_error);
}

TEST_CASE("Non-capturing Square functor") {
	struct Square
	{
		int operator()(int i) { return i * i; }
	};
	Square s1;

	Mehrdad::Function<int(int)> f1(s1);

	REQUIRE(f1(10) == 100);
	REQUIRE(f1(5) == 25);
}

TEST_CASE("Non-capturing lambda") {
	Mehrdad::Function<double(double)> ff([](double radius){ return radius * radius * 3.14; });

	REQUIRE(ff(10) == 314);
}

TEST_CASE("Capturing string lookup functor") {
	struct HasPattern
	{
		HasPattern(const std::string& pattern): mPattern(pattern){}
		bool operator()(const std::string str) { return str.find(mPattern) != std::string::npos; }
	private:
		std::string mPattern;
	};
	HasPattern lookup("Waldo");

	Mehrdad::Function<bool(const std::string&)> f1(lookup);

	REQUIRE(f1("This one doesn't have it") == false);
	REQUIRE(f1("Here you can find Waldo") == true);
}

TEST_CASE("Capturing lambda") {

	int counter = 5;
	Mehrdad::Function<int(int, int)> f(
				[&counter](int add1, int add2){
		return (add1 + add2) * counter++;
	});

	REQUIRE(f(2, 3) == 25);
	REQUIRE(f(2, 3) == 30);
	counter = 12;
	REQUIRE(f(2, 1) == 36);
}
