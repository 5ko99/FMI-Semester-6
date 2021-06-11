#pragma once
#include "catch.hpp"
#include "Vehicle.h"

TEST_CASE("Throws exception if vehicle with same registration exists", "[Vehicle]")
{
	Vehicle v1(Registration("AB1111XY"), "car");
	REQUIRE_THROWS(Vehicle(Registration("AB1111XY"), "car 2"));
}
