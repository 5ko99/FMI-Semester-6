#include "catch_amalgamated.hpp"

#include "Registration.h"

TEST_CASE("Constructing with c-string", "[Registration]")
{
	Registration _1("C1234AB");
	Registration _2("XY1111YX");

	REQUIRE_THROWS_AS(Registration("111145"), std::invalid_argument);
	REQUIRE_THROWS_AS(Registration("C1234ab"), std::invalid_argument);
	REQUIRE_THROWS_AS(Registration("ABC34DEF"), std::invalid_argument);
	REQUIRE_THROWS_AS(Registration("ABCDEF"), std::invalid_argument);
	REQUIRE_THROWS_AS(Registration("C11D"), std::invalid_argument);
}
