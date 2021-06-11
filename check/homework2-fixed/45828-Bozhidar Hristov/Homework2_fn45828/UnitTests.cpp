#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include "Vehicle.h"
#include "catch.hpp"

TEST_CASE("Registration") {
	char reg[9] = "AS1234AS";
	Registration r1(reg);
	REQUIRE(strcmp(r1.getReg(), "AS1234AS") == 0);
}

TEST_CASE("Person") {
	Person p1("pesho", 123);
	REQUIRE(p1.getName() == "pesho");
	REQUIRE(p1.getId() == 123);
	REQUIRE(p1.getVehicles() == nullptr);
	REQUIRE(p1.getVehiclesCount() == 0);
}

TEST_CASE("Vehicle") {
	char reg[9] = "AS1234AS";
	Registration r1(reg);
	Vehicle v1(r1, "description");
	REQUIRE(strcmp(v1.getRegistration().getReg(), r1.getReg()) == 0);
	REQUIRE(v1.getDescription() == "description");
}
