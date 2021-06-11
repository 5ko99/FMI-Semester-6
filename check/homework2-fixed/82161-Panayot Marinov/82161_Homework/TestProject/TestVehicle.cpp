#include "catch2.hpp"
#include "../MainProject/Headers/Person.h"
#include "../MainProject/Headers/Vehicle.h"
#include <string>

using std::string;

TEST_CASE( "Vehicle instances can be created correctly") {
    SECTION("Testing constructor with char*") {
        Vehicle vehicle("CA1111AA", "A simple vehicle");
        REQUIRE(vehicle.getRegistration() == "CA1111AA");
        REQUIRE(vehicle.getDesctiption() == "A simple vehicle");
        REQUIRE(!vehicle.hasOwner());
        REQUIRE_THROWS_AS(vehicle.getOwner(), std::logic_error);
        CHECK_THROWS_AS(vehicle.getOwner(), std::logic_error);
    }

    SECTION("Testing constructor with strings") {
        Vehicle vehicle(string("CA1111AA"), string("A simple vehicle"));
        REQUIRE(vehicle.getRegistration() == "CA1111AA");
        REQUIRE(vehicle.getDesctiption() == "A simple vehicle");
        REQUIRE(!vehicle.hasOwner());
        REQUIRE_THROWS_AS(vehicle.getOwner(), std::logic_error);
        CHECK_THROWS_AS(vehicle.getOwner(), std::logic_error);
    }

    SECTION("Testing constructor with Registration and string") {
        Vehicle vehicle(Registration("CA1111AA"), string("A simple vehicle"));
        REQUIRE(vehicle.getRegistration() == "CA1111AA");
        REQUIRE(vehicle.getDesctiption() == "A simple vehicle");
        REQUIRE(!vehicle.hasOwner());
        REQUIRE_THROWS_AS(vehicle.getOwner(), std::logic_error);
        CHECK_THROWS_AS(vehicle.getOwner(), std::logic_error);
    }
}

TEST_CASE( "Testing Vehicle operator==") {
    SECTION("Testing with 2 equal objects without owners") {
        Vehicle vehicle("CA1111AA", "A simple vehicle");
        Vehicle* vehicle2 = &vehicle;
        REQUIRE((vehicle == *vehicle2) == true);
    }

    SECTION("Testing with 2 equal objects with owners") {
        Vehicle vehicle("CA1111AA", "A simple vehicle");
        Vehicle* vehicle2 = &vehicle;
        Person person("Ivancho");
        vehicle.setOwner(&person);
        REQUIRE((vehicle == *vehicle2) == true);
    }

    SECTION("Testing with 2 equal objects with owner and no owner") {
        Vehicle vehicle("CA1111AA", "A simple vehicle");
        Vehicle vehicle2("CA1111AA", "A simple vehicle");
        Person person("Ivancho");
        vehicle.setOwner(&person);
        REQUIRE((vehicle == vehicle2) == false);
    }

    SECTION("Testing with 2 non-equal objects") {
        Vehicle vehicle("CA1111AA", "A simple vehicle");
        Vehicle vehicle2(Registration("CA1111AB"), string("A simple vehicle"));
        REQUIRE((vehicle == vehicle2) == false);
    }
}

TEST_CASE( "Testing Vehicle removeOwner function") {
    SECTION("Testing with 2 equal objects") {
        Vehicle vehicle("CA1111AA", "A simple vehicle");
        Person person("Ivan");
        vehicle.setOwner(&person);
        vehicle.removeOwner(&person);
        REQUIRE(!vehicle.hasOwner());
        REQUIRE_THROWS_AS(vehicle.getOwner(), std::logic_error);
        CHECK_THROWS_AS(vehicle.getOwner(), std::logic_error);
    }
}

TEST_CASE( "Testing Vehicle setOwner and hasOwner functions") {
    SECTION("Testing with 2 equal objects") {
        Vehicle vehicle("CA1111AA", "A simple vehicle");
        REQUIRE(vehicle.hasOwner() == false);
        Person person("Ivan");
        vehicle.setOwner(&person);
        REQUIRE(vehicle.hasOwner() == true);
        REQUIRE((person == vehicle.getOwner()) == true);
    }
}
