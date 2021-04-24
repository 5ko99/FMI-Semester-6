#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Garage/garage.h"

TEST_CASE("Garage constructors, assignment and empty")
{
    Garage garage1(3);

    SECTION("test empty when true")
    {
        REQUIRE(garage1.empty() == true);
    }

    SECTION("test empty when false")
    {
        Vehicle vehicle1("12345", "description", 2);
        garage1.insert(vehicle1);

        REQUIRE(garage1.empty() == false);
    }

    SECTION("test copy constructor")
    {
        Vehicle vehicle1("12345", "description", 2);
        garage1.insert(vehicle1);

        Garage garage2(garage1);

        REQUIRE(*garage2.find("12345") == vehicle1);
    }

    SECTION("test operator =")
    {
        Vehicle vehicle1("12345", "description", 2);
        garage1.insert(vehicle1);

        Garage garage2 = garage1;

        REQUIRE(*garage2.find("12345") == vehicle1);
    }
}

TEST_CASE("Garage insert and getters")
{
    Garage garage1(3);

    SECTION("test insert, operator [] and at")
    {
        Vehicle vehicle1("12345", "description", 2);
        garage1.insert(vehicle1);

        REQUIRE(garage1[0] == vehicle1);
        REQUIRE(garage1.at(0) == vehicle1);
    }

    SECTION("test insert in full garage exception")
    {
        Vehicle vehicle1("12345", "description", 4);

        REQUIRE_THROWS_AS(garage1.insert(vehicle1), std::invalid_argument);
    }

    SECTION("test at exception")
    {
        REQUIRE_THROWS_AS(garage1.at(3), std::out_of_range);
    }

    SECTION("test size getter")
    {
        Vehicle vehicle1("12345", "description", 2);
        garage1.insert(vehicle1);

        Vehicle vehicle2("67890", "smth", 1);
        garage1.insert(vehicle2);

        REQUIRE(garage1.size() == 2);
    }
}

TEST_CASE("Garage erser and clearer")
{
    Garage garage1(3);

    SECTION("test erase")
    {
        Vehicle vehicle1("12345", "description", 2);
        garage1.insert(vehicle1);

        garage1.erase("12345");

        REQUIRE(&garage1[0] == nullptr);
    }

    SECTION("test erase for non existent item")
    {
        Vehicle vehicle1("12345", "description", 2);
        garage1.insert(vehicle1);

        garage1.erase("00000");

        REQUIRE(&garage1[0] != nullptr);
    }

    SECTION("test clear")
    {
        Vehicle vehicle1("12345", "description", 2);
        garage1.insert(vehicle1);

        Vehicle vehicle2("67890", "smth", 1);
        garage1.insert(vehicle2);

        garage1.clear();

        REQUIRE(garage1.size() == 0);
    }
}

TEST_CASE("Garage find")
{
    Garage garage1(3);

    SECTION("test find")
    {
        Vehicle vehicle1("12345", "description", 2);
        garage1.insert(vehicle1);

        Vehicle vehicle2("67890", "smth", 1);
        garage1.insert(vehicle2);

        const Vehicle *vehicle3 = garage1.find("67890");

        REQUIRE(strcmp(vehicle3->getDescription(), "smth") == 0);
    }

    SECTION("test find with non existent item")
    {
        Vehicle vehicle1("12345", "description", 2);
        garage1.insert(vehicle1);

        Vehicle vehicle2("67890", "smth", 1);
        garage1.insert(vehicle2);

        const Vehicle *vehicle3 = garage1.find("0000");

        REQUIRE(vehicle3 == nullptr);
    }
}