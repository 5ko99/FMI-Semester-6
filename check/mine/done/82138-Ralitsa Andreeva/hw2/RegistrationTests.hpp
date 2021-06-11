#pragma once
#include "catch.hpp"
#include "Registration.h"

TEST_CASE("Valid registration", "[Registration]")
{
	REQUIRE_NOTHROW(Registration("C1234AB"));
	REQUIRE_NOTHROW(Registration("XY1111YX"));
}
TEST_CASE("Invalid length", "[Registration]")
{
	REQUIRE_THROWS(Registration("AB111Y"));
	REQUIRE_THROWS(Registration("ABCDF1111YZ"));
}
TEST_CASE("Invalid number of digits", "[Registration]")
{
	REQUIRE_THROWS(Registration("A11111XY"));
	REQUIRE_THROWS(Registration("B11BC"));
}
TEST_CASE("Invalid number of letters", "[Registration]")
{
	REQUIRE_THROWS(Registration("AC1111X"));
	REQUIRE_THROWS(Registration("BBB1111B"));
}
TEST_CASE("Invalid if registration contains small letters", "[Registration]")
{
	REQUIRE_THROWS(Registration("c1234AB"));
	REQUIRE_THROWS(Registration("XY1111yx"));
}

