#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()

#include "function.h"
#include "catch.hpp"

TEST_CASE("Empty functions") {
	Mehrdad::Function<int, double> f1;
	Mehrdad::Function<double, int> f2(nullptr);

	REQUIRE( static_cast<bool>(f1) == false );
	REQUIRE( static_cast<bool>(f2) == false );

	REQUIRE_THROWS_AS(f1(1.0), std::runtime_error);
	REQUIRE_THROWS_AS(f2(1), std::runtime_error);
}
