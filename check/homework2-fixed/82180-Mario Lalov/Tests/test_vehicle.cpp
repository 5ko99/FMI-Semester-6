#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Vehicle/vehicle.h"
#include "../Person/person.h"

TEST_CASE("constructors")
{
    SECTION("registration format errors")
    {
        SECTION("lower case registration")
        {
            REQUIRE_THROWS_AS(Vehicle("c1234xx", "desc"), std::invalid_argument);
            REQUIRE_THROWS_AS(Vehicle("Ca1234XX", "desc"), std::invalid_argument);
        }

        SECTION("incorrect registration arrangement")
        {
            REQUIRE_THROWS_AS(Vehicle("12345", "desc"), std::invalid_argument);
            REQUIRE_THROWS_AS(Vehicle("C12345XX", "desc"), std::invalid_argument);
            REQUIRE_THROWS_AS(Vehicle("C1234X2", "desc"), std::invalid_argument);
            REQUIRE_THROWS_AS(Vehicle("C12341X", "desc"), std::invalid_argument);
            REQUIRE_THROWS_AS(Vehicle("CA12345X", "desc"), std::invalid_argument);
            REQUIRE_THROWS_AS(Vehicle("12345XX", "desc"), std::invalid_argument);
            REQUIRE_THROWS_AS(Vehicle("1C3456XX", "desc"), std::invalid_argument);
        }
    }

    SECTION("used resgistration error")
    {
        Vehicle vehicle1("CA1234XX", "desc");

        REQUIRE_THROWS_AS(Vehicle("CA1234XX", "smth"), std::invalid_argument);
    }
}

TEST_CASE("getters")
{
    Vehicle vehicle("CA1234XX", "desc");

    REQUIRE(vehicle.getRegistration() == "CA1234XX");
    REQUIRE(vehicle.getDescription() == "desc");
}

TEST_CASE("owner")
{
    Vehicle vehicle("CA1234XX", "desc");
    Person person1(1, "pesho");

    vehicle.setOwner(&person1);

    SECTION("check if owned")
    {
        REQUIRE(vehicle.checkIfOwned());
        REQUIRE(vehicle.getOwner()->getId() == person1.getId()); 
    }

    SECTION("check vehicle disowning")
    {
        vehicle.removeOwner();

        REQUIRE(!vehicle.checkIfOwned());
    }
}
