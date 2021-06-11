#pragma once

#include "catch.hpp"
#include "../PersonAndVehicles/Registration.h"

TEST_CASE("Testing constuction of registration")
{
	REQUIRE_THROWS(Registration(""));
	REQUIRE_THROWS(Registration("a"));
	REQUIRE_THROWS(Registration("1234"));
	REQUIRE_THROWS(Registration("abcdefg"));
	REQUIRE_THROWS(Registration("AAAAAAA"));
	REQUIRE_THROWS(Registration("c1234cc"));
	REQUIRE_THROWS(Registration("b1234CC"));
	REQUIRE_THROWS(Registration("BBB1234CC"));
	REQUIRE_THROWS(Registration("BB1-234CC"));
	REQUIRE_THROWS(Registration("BB12F34C"));
	REQUIRE_THROWS(Registration("CC1234CC\n"));
	REQUIRE_THROWS(Registration(" CC1234CC"));

	REQUIRE_NOTHROW(Registration("C1234CC"));
	REQUIRE_NOTHROW(Registration("CA0123BK"));
	REQUIRE_NOTHROW(Registration("CC1234CC"));
	REQUIRE_NOTHROW(Registration("ZZ1234FK"));
	REQUIRE_NOTHROW(Registration("ZZ0000FK"));
}

TEST_CASE("Testing getRegistrationString() method")
{
	REQUIRE(Registration("AB1234CC").getRegistrationString() == "AB1234CC");
	REQUIRE(Registration("A1234CC").getRegistrationString() == "A1234CC");
	REQUIRE(Registration("AB0000CC").getRegistrationString() == "AB0000CC");
	REQUIRE(Registration("ZZ8764ZZ").getRegistrationString() == "ZZ8764ZZ");
	REQUIRE(Registration("PL9999SS").getRegistrationString() == "PL9999SS");
}
