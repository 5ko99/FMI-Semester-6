#include "catch_amalgamated.hpp"
#include "Person.h"

TEST_CASE("Constructor tests for Person")
{
    SECTION("Default constructor")
    {
        Person person;
        REQUIRE(person.getId() == 0);
        REQUIRE(strcmp(person.getName(), "") == 0);
    }

    SECTION("Constructor with name and id")
    {
        Person person = Person("Tony stark", 12);
        REQUIRE(person.getId() == 12);
        REQUIRE(strcmp(person.getName(), "Tony stark") == 0);
    }
}

TEST_CASE("Public methods test")
{
    SECTION("Adding vehicle")
    {
        Person person = Person("Tony stark", 12);
        Vehicle first = Vehicle("CB1234AB", "Batmobile");
        REQUIRE_FALSE(first.isOwned());
        person.addVehicle(first);
        REQUIRE(first.isOwned());
        REQUIRE(strcmp(first.getOwner().getName(), person.getName()) == 0);
        REQUIRE(strcmp(person.getVehicle("CB1234AB").getDescription(), first.getDescription()) == 0);
    }

    SECTION("Removing vehicle")
    {
        Person person = Person("Jack Sparrow", 5);
        Vehicle first = Vehicle("OK1234KO", "Black pearl");
        Vehicle second = Vehicle("KO1467OK", "Pearl black");
        REQUIRE_FALSE(first.isOwned());
        REQUIRE_FALSE(second.isOwned());
        REQUIRE_FALSE(person.hasVehicle());
        person.addVehicle(first);
        person.addVehicle(second);
        REQUIRE(first.isOwned());
        REQUIRE(second.isOwned());
        REQUIRE(person.hasVehicle());
        person.removeVehicle(first);
        REQUIRE_FALSE(first.isOwned());
        REQUIRE(second.isOwned());
        REQUIRE(person.hasVehicle());
        person.addVehicle(first);
        REQUIRE(first.isOwned());
        person.removeAllVehicles();
        REQUIRE_FALSE(first.isOwned());
        REQUIRE_FALSE(second.isOwned());
        REQUIRE_FALSE(person.hasVehicle());
    }

    SECTION("Getting vehicle")
    {
        Person person = Person("Jack Sparrow", 5);
        Vehicle first = Vehicle("OK1234KO", "Black pearl");
        person.addVehicle(first);
        Vehicle second = person.getVehicle("OK1234KO");
        REQUIRE(strcmp(second.getDescription(), first.getDescription()) == 0);
    }

    SECTION("Getting parameters")
    {
        Person person = Person("Jack Sparrow", 5);
        REQUIRE(strcmp(person.getName(), "Jack Sparrow") == 0);
        REQUIRE(person.getId() == 5);
    }
}
