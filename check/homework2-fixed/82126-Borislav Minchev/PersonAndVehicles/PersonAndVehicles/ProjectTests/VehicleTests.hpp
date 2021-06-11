#pragma once

#include "catch.hpp"
#include "../PersonAndVehicles/Vehicle.h"

TEST_CASE("Testing constuction of vehicle")
{
	SECTION("Testing constuction of vehicle with std::string argument")
	{
		REQUIRE_THROWS(Vehicle("", "des"));
		REQUIRE_THROWS(Vehicle("a", "des"));
		REQUIRE_THROWS(Vehicle("1234", "des"));
		REQUIRE_THROWS(Vehicle("abcdefg", "des"));
		REQUIRE_THROWS(Vehicle("c1234cc", "des"));
		REQUIRE_THROWS(Vehicle("BBB1234CC", "des"));
		REQUIRE_THROWS(Vehicle("BB1-234CC", "des"));
		REQUIRE_THROWS(Vehicle("CC1234CC\n", "des"));

		REQUIRE_NOTHROW(Vehicle("C1234CC", "des"));
		REQUIRE_NOTHROW(Vehicle("CA0123BK", "des"));
		REQUIRE_NOTHROW(Vehicle("CC1234CC", "des"));
		REQUIRE_NOTHROW(Vehicle("ZZ1234FK", "des"));
		REQUIRE_NOTHROW(Vehicle("ZZ0000FK", "des"));
	}

	SECTION("Testing constuction of vehicle with Registration argument")
	{
		REQUIRE_THROWS(Vehicle(Registration(""), "des"));
		REQUIRE_THROWS(Vehicle(Registration("a"), "des"));
		REQUIRE_THROWS(Vehicle(Registration("1234"), "des"));
		REQUIRE_THROWS(Vehicle(Registration("abcdefg"), "des"));
		REQUIRE_THROWS(Vehicle(Registration("c1234cc"), "des"));
		REQUIRE_THROWS(Vehicle(Registration("BBB1234CC"), "des"));
		REQUIRE_THROWS(Vehicle(Registration("BB1-234CC"), "des"));
		REQUIRE_THROWS(Vehicle(Registration("CC1234CC\n"), "des"));

		REQUIRE_NOTHROW(Vehicle(Registration("C1234CC"), "des"));
		REQUIRE_NOTHROW(Vehicle(Registration("CA0123BK"), "des"));
		REQUIRE_NOTHROW(Vehicle(Registration("CC1234CC"), "des"));
		REQUIRE_NOTHROW(Vehicle(Registration("ZZ1234FK"), "des"));
		REQUIRE_NOTHROW(Vehicle(Registration("ZZ0000FK"), "des"));
	}
}

TEST_CASE("Testing getter methods of vehicle") 
{
	SECTION("Testing getRegistration()")
	{
		REQUIRE(Vehicle("C1234CC", "des").getRegistration().getRegistrationString() == "C1234CC");
		REQUIRE(Vehicle("CA0123BK", "des").getRegistration().getRegistrationString() == "CA0123BK");
		REQUIRE(Vehicle("CC1234CC", "des").getRegistration().getRegistrationString() == "CC1234CC");
		REQUIRE(Vehicle("ZZ1234FK", "des").getRegistration().getRegistrationString() == "ZZ1234FK");
		REQUIRE(Vehicle("ZZ0000FK", "des").getRegistration().getRegistrationString() == "ZZ0000FK");
	}
	SECTION("Testing getDescription()")
	{
		REQUIRE(Vehicle("C1234CC", "").getRegistration().getRegistrationString() == "C1234CC");
		REQUIRE(Vehicle("C1234CC", "aaaaa").getRegistration().getRegistrationString() == "C1234CC");
		REQUIRE(Vehicle("C1234CC", "Abc123PPll").getRegistration().getRegistrationString() == "C1234CC");
		REQUIRE(Vehicle("C1234CC", "(^o^)").getRegistration().getRegistrationString() == "C1234CC"); 
		REQUIRE(Vehicle("C1234CC", "aaaaa").getRegistration().getRegistrationString() == "C1234CC");
	}
}

SCENARIO("Testing relation of vehicle with owner")
{
	GIVEN ("Vehicle and person with no relation between them")
	{
		Person p(1, "abc");
		Vehicle v1("CC1234CC", "desr1");
		REQUIRE(!v1.hasOwner());
		WHEN("Vehicle is owned by the person")
		{
			v1.setOwner(p);
			THEN("Person is set correctly")
			{
				REQUIRE(v1.hasOwner());
				REQUIRE(v1.getOwner() == &p);
			}
			
		}
	}
	GIVEN("Vehicle with owner and vehicle with no owner")
	{
		Person p(1, "abc"), m(2,"bbb");
		Vehicle v1("CC1234CC", "desr1"), v2("AB1234BA", "descr2");
		v1.setOwner(p);
		WHEN("We try to set new owner directly")
		{
			THEN("exception is thrown")
			{
				REQUIRE_THROWS(v1.setOwner(m));
			}
		}
		WHEN("we remove old owner and then set new one")
		{
			REQUIRE_NOTHROW(v1.removeOwner());
			THEN("Everything executes correctly")
			{
				REQUIRE_NOTHROW(v1.setOwner(m));
				REQUIRE(v1.hasOwner());
				REQUIRE(v1.getOwner() == &m);
			}
		}
	}
}
