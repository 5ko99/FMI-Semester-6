#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Vehicle/vehicle.h"

TEST_CASE("Vehicle")
{
    SECTION("test geters")
    {
        Vehicle vehicle1("123456", "this is description", 4);

        REQUIRE(strcmp(vehicle1.getRegistration(), "123456") == 0);
        REQUIRE(strcmp(vehicle1.getDescription(), "this is description") == 0);
        REQUIRE(vehicle1.getSpaces() == 4);
    }

    SECTION("test operator =")
    {
        Vehicle vehicle1("123456", "this is description", 4);
        Vehicle vehicle2("673745", "smth", 4);
        vehicle2 = vehicle1;

        REQUIRE(strcmp(vehicle1.getRegistration(), vehicle2.getRegistration()) == 0);
        REQUIRE(strcmp(vehicle1.getDescription(), vehicle2.getDescription()) == 0);
        REQUIRE(vehicle1.getSpaces() == vehicle2.getSpaces());
    }

    SECTION("test operator == when true")
    {
        Vehicle vehicle1("123456", "this is description", 4);
        Vehicle vehicle2("123456", "smth", 4);

        REQUIRE(vehicle1 == vehicle2);
    }

    SECTION("test operator == when false")
    {
        Vehicle vehicle1("123456", "this is description", 4);
        Vehicle vehicle2("127896", "smth", 4);

        REQUIRE(!(vehicle1 == vehicle2));
    }
}