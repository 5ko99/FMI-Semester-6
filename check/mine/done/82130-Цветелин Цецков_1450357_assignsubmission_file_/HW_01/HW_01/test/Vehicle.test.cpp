#include "catch_amalgamated.hpp"
#include "Vehicle.h"

#include <cstddef>
#include <stdexcept>

TEST_CASE("Vehicle constructs correct data", "[Vehicle]") {
	const char* registration = "M 8888 AB";
	const char* description = "Stara lada niva";
	std::size_t size = 4;

	Vehicle variableVeh(registration, description, size);

	REQUIRE(strcmp(variableVeh.registration(), registration) == 0);
	REQUIRE(strcmp(variableVeh.description(), description) == 0);
	REQUIRE(variableVeh.size() == size);
}

TEST_CASE("Vehicle copy constructor copies", "[Vehicle]") {
	const char* registration = "M 8888 AB";
	const char* description = "Stara lada niva";
	std::size_t size = 4;

	Vehicle variableVeh(registration, description, size);
	Vehicle copyConstructed = variableVeh;

	REQUIRE(strcmp(variableVeh.registration(), copyConstructed.registration()) == 0);
	REQUIRE(variableVeh.registration() != copyConstructed.registration());
	REQUIRE(strcmp(variableVeh.description(), copyConstructed.description()) == 0);
	REQUIRE(variableVeh.description() != copyConstructed.description());
	REQUIRE(variableVeh.size() == copyConstructed.size());
}

TEST_CASE("Vehicle ==operator", "[Vehicle]") {
	const char* registration = "M 8888 AB";
	const char* description = "Stara lada niva";
	std::size_t size = 4;

	Vehicle variableVeh(registration, description, size);
	Vehicle copyConstructed = variableVeh;

	REQUIRE(variableVeh == copyConstructed);
}

TEST_CASE("Vehicle constructor throws with 0 size", "[Vehicle]") {
	const char* registration = "M 8888 AB";
	const char* description = "Stara lada niva";
	std::size_t size = 0;

	REQUIRE_THROWS_AS(Vehicle(registration, description, size), std::invalid_argument);
}