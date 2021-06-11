#include "catch_amalgamated.hpp"
#include "Vehicle.h"
#include "Person.h"

TEST_CASE("Creation without conflicts, without owner", "[Vehicle]")
{
	Vehicle _1("AB1234AB", "Description");
	Vehicle _2("C5678CD", "Description2");
}

TEST_CASE("Creation with same registration, without owner", "[Vehicle]")
{
	Vehicle _1("AB1234AB", "Description");
	REQUIRE_THROWS_AS(Vehicle("AB1234AB", "Description2"), std::invalid_argument);
}

TEST_CASE("Cleaning after deletion", "[Vehicle]")
{
	Vehicle _1("AB1234AB", "Description");
	Vehicle* _2 = new Vehicle("C5678CD", "Description2");

	REQUIRE_THROWS_AS(Vehicle("C5678CD", "Description2"), std::invalid_argument);

	delete _2;
	REQUIRE_NOTHROW(Vehicle("C5678CD", "Description2"));
}
