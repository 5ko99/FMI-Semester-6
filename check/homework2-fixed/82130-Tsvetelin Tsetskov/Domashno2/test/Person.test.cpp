#include "catch_amalgamated.hpp"
#include "Person.h"
#include "Vehicle.h"

#include <string>

TEST_CASE("Person creating without conflicts", "[Person]")
{
	Person pesho("Pesho", 1);
	Person gosho("Gosho", 2);
}

TEST_CASE("Person creating with conflicts", "[Person]")
{
	Person pesho("Pesho", 1);
	Person gosho("Gosho", 2);

	REQUIRE_THROWS_AS(Person("Tosho", 2), std::invalid_argument);
}

TEST_CASE("Person creating after destruction", "[Person]")
{
	Person pesho("Pesho", 1);
	Person* gosho = new Person("Gosho", 2);

	REQUIRE_THROWS_AS(Person("Tosho", 2), std::invalid_argument);

	delete gosho;
	REQUIRE_NOTHROW(Person("Tosho", 2));
}

