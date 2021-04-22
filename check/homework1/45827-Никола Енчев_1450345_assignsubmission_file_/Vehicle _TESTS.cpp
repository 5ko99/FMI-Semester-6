
// to use the test coment out main_4.cpp

#include "Vehicle.h"
#include "catch.hpp"
#include <iostream>

TEST_CASE("Vehicle : constructor and get funcitons")
{
	Vehicle a{ "123","Big and fast", 42 };

	REQUIRE(strcmp(a.getRegistration(), "123") == 0);
	REQUIRE(strcmp(a.getDescription(), "Big and fast") == 0);
	REQUIRE(a.getSpace() == 42);

}
