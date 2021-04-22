#ifndef VEHICLETESTS_H
#define VEHICLETESTS_H

#include "catch.h"
#include "../Classes/Vehicle.h"

TEST_CASE("Vehicle constructor works correct", "[Vehicle]")
{
	Vehicle v1 = Vehicle("Aa1234bB", "My first car", 1);
	Vehicle v2 = Vehicle("Bb5678cC", "My second car", 2);
	Vehicle v3 = Vehicle("Cc91011dD", "My third car", 9);
	Vehicle v4 = Vehicle("Dd121314eE", "My fourth car", 15);

	SECTION("Constructor sets correct registration")
	{
		REQUIRE(MyString(v1.registration()) == MyString("Aa1234bB"));
		REQUIRE(MyString(v2.registration()) == MyString("Bb5678cC"));
		REQUIRE(MyString(v3.registration()) == MyString("Cc91011dD"));
		REQUIRE(MyString(v4.registration()) == MyString("Dd121314eE"));
	}

	SECTION("Constructor sets correct description")
	{
		REQUIRE(MyString(v1.description()) == MyString("My first car"));
		REQUIRE(MyString(v2.description()) == MyString("My second car"));
		REQUIRE(MyString(v3.description()) == MyString("My third car"));
		REQUIRE(MyString(v4.description()) == MyString("My fourth car"));
	}

	SECTION("Constructor sets correct parkingSpotNumber")
	{
		REQUIRE(v1.space() == 1);
		REQUIRE(v2.space() == 2);
		REQUIRE(v3.space() == 9);
		REQUIRE(v4.space() == 15);
	}
}

TEST_CASE("Vehicle function registration works correct", "[Vehicle]")
{
	Vehicle v1 = Vehicle("Aa1234bB", "My first car", 1);
	Vehicle v2 = Vehicle("Bb5678cC", "My second car", 2);
	Vehicle v3 = Vehicle("Cc91011dD", "My third car", 9);
	Vehicle v4 = Vehicle("Dd121314eE", "My fourth car", 15);

	SECTION("Function registration returns correct value")
	{
		REQUIRE(MyString(v1.registration()) == MyString("Aa1234bB"));
		REQUIRE(MyString(v2.registration()) == MyString("Bb5678cC"));
		REQUIRE(MyString(v3.registration()) == MyString("Cc91011dD"));
		REQUIRE(MyString(v4.registration()) == MyString("Dd121314eE"));
	}
}

TEST_CASE("Vehicle function description works correct", "[Vehicle]")
{
	Vehicle v1 = Vehicle("Aa1234bB", "My first car", 1);
	Vehicle v2 = Vehicle("Bb5678cC", "My second car", 2);
	Vehicle v3 = Vehicle("Cc91011dD", "My third car", 9);
	Vehicle v4 = Vehicle("Dd121314eE", "My fourth car", 15);

	SECTION("function description returns correct value")
	{
		REQUIRE(MyString(v1.description()) == MyString("My first car"));
		REQUIRE(MyString(v2.description()) == MyString("My second car"));
		REQUIRE(MyString(v3.description()) == MyString("My third car"));
		REQUIRE(MyString(v4.description()) == MyString("My fourth car"));
	}
}

TEST_CASE("Vehicle function space works correct", "[Vehicle]")
{
	Vehicle v1 = Vehicle("Aa1234bB", "My first car", 1);
	Vehicle v2 = Vehicle("Bb5678cC", "My second car", 2);
	Vehicle v3 = Vehicle("Cc91011dD", "My third car", 9);
	Vehicle v4 = Vehicle("Dd121314eE", "My fourth car", 15);

	SECTION("Function space returns correct value")
	{
		REQUIRE(v1.space() == 1);
		REQUIRE(v2.space() == 2);
		REQUIRE(v3.space() == 9);
		REQUIRE(v4.space() == 15);
	}
}
#endif VEHICLETESTS_H