#pragma once

#include "catch.hpp"
#include "../PersonAndVehicles/Person.h"

TEST_CASE("Testing constucion of person object")
{
	REQUIRE_NOTHROW(Person(1,"abc"));
	REQUIRE_NOTHROW(Person(0, "abc"));
	REQUIRE_NOTHROW(Person(UINT32_MAX, "abc"));
	
	REQUIRE_NOTHROW(Person(1, ""));
	REQUIRE_NOTHROW(Person(1, "Goshko"));
	REQUIRE_NOTHROW(Person(1, "Hgjhgdjhagsdo ***kdsag(0^529125%#@!"));
}

TEST_CASE("Testing getter methods of person")
{
	SECTION("Testing getId()")
	{
		REQUIRE_NOTHROW(Person(1, "abc"). getId() == 1);
		REQUIRE_NOTHROW(Person(0, "abc").getId() == 0);
		REQUIRE_NOTHROW(Person(UINT32_MAX, "abc").getId() == UINT32_MAX);
	}

	SECTION("Testing getName()")
	{
		REQUIRE_NOTHROW(Person(1, "").getName() == "");
		REQUIRE_NOTHROW(Person(1, "abc").getName() == "abc");
		REQUIRE_NOTHROW(Person(1, "a").getName() == "a");
		REQUIRE_NOTHROW(Person(1, "GGGiiPPP").getName() == "GGGiiPPP");
		REQUIRE_NOTHROW(Person(1, "abcjhdksjah jasdkjhd $#$@#@&**(-_-)/").getName() == "abcjhdksjah jasdkjhd $#$@#@&**(-_-)/");
	}
}

TEST_CASE("Testing addVehicle() and getVehicles() methods")
{
	Person p(1, "abc");
	REQUIRE(p.getVehicles().size() == 0);

	Vehicle v1("CC1234CC", "desr1"), v2("AB1234CD", "desr2"), v3("KK1234SS", "desr3");

	p.addVehicle(v1);
	REQUIRE(p.getVehicles().size() == 1);
	REQUIRE(p.getVehicles()[0] == &v1);

	p.addVehicle(v2);
	REQUIRE(p.getVehicles().size() == 2);
	REQUIRE(p.getVehicles()[1] == &v2);

	p.addVehicle(v3);
	REQUIRE(p.getVehicles().size() == 3);
	REQUIRE(p.getVehicles()[2] == &v3);

	REQUIRE_THROWS(p.addVehicle(v3));
}

TEST_CASE("Testing removing vehicle")
{
	Person p(1, "abc");
	Vehicle v1("CC1234CC", "desr1"), v2("AB1234CD", "desr2"), v3("KK1234SS", "desr3");
	p.addVehicle(v1);
	p.addVehicle(v2);
	p.addVehicle(v3);

	REQUIRE(p.getVehicles().size() == 3);
	
	p.removeVehicle("CC1234CC");
	REQUIRE(p.getVehicles().size() == 2);

	p.removeVehicle("FF1234FF");//not existing
	REQUIRE(p.getVehicles().size() == 2);

	p.removeVehicle("AB1234CD");
	REQUIRE(p.getVehicles().size() == 1);

	p.removeVehicle("KK1234SS");
	REQUIRE(p.getVehicles().size() == 0);
}

TEST_CASE("Testing finding vehicle")
{
	Person p(1, "abc");
	Vehicle v1("CC1234CC", "desr1"), v2("AB1234CD", "desr2"), v3("KK1234SS", "desr3");
	p.addVehicle(v1);
	p.addVehicle(v2);
	p.addVehicle(v3);

	REQUIRE(p.findVehicle("CC1234CC") == &v1);
	REQUIRE(p.findVehicle("SS1234SS") == nullptr);//not existing veicle
	REQUIRE(p.findVehicle("AB1234CD") == &v2);
	REQUIRE(p.findVehicle("KK1234SS") == &v3);
}
