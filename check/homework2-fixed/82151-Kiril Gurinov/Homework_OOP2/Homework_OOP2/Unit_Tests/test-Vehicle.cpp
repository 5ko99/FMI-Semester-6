#include "catch_amalgamated.hpp"
#include "Vehicle.h"

TEST_CASE("Constructor tests for Vehicle")
{
    SECTION("Default constructor")
    {
        Vehicle vehicle;
        REQUIRE(vehicle.isOwned() == false);
        REQUIRE(vehicle.getDescription() == "");
    }

    SECTION("Constructor with registration")
    {
        Vehicle vehicle = Vehicle("C1234AB");
        REQUIRE(vehicle.isOwned() == false);
        REQUIRE(strcmp(vehicle.getDescription(), "") == 0);
        REQUIRE(strcmp(vehicle.getRegistration(), "C1234AB") == 0);
    }

    SECTION("Constructor with registration and description")
    {
        Vehicle vehicle = Vehicle("C1234AB", "Lada");
        REQUIRE(vehicle.isOwned() == false);
        REQUIRE(strcmp(vehicle.getDescription(), "Lada") == 0);
        REQUIRE(strcmp(vehicle.getRegistration(), "C1234AB") == 0);
    }
}

TEST_CASE("Public methods test")
{
    SECTION("Getting parameters")
    {
        Vehicle vehicle = Vehicle("C1234AB", "Lada");
        REQUIRE(strcmp(vehicle.getRegistration(), "C1234AB")== 0);
        REQUIRE(strcmp(vehicle.getDescription(), "Lada")== 0);
        REQUIRE(&vehicle.getOwner() == nullptr);
    }
    SECTION("Description change")
    {
        Vehicle vehicle = Vehicle("C1234AB", "Lada");
        REQUIRE(strcmp(vehicle.getDescription(), "Lada") == 0);
        vehicle.setDescription("Opel");
        REQUIRE(strcmp(vehicle.getDescription(), "Opel") == 0);
    }
    SECTION("Number change")
    {
        Vehicle vehicle = Vehicle("C1234AB", "Lada");
        REQUIRE(strcmp(vehicle.getRegistration(), "C1234AB") == 0);
        vehicle.setNumber("CA5151BA");
        REQUIRE(strcmp(vehicle.getRegistration(), "CA5151BA") == 0);
    }
    SECTION("Add owner")
    {
        Vehicle vehicle = Vehicle("C1234AB", "Lada");
        Person person = Person("Batman", 15);
        REQUIRE(vehicle.isOwned() == false);
        vehicle.addOwner(person);
        REQUIRE(vehicle.isOwned() == true);
        REQUIRE(vehicle.getOwner().getId() == person.getId());
        REQUIRE(strcmp(vehicle.getOwner().getName(), person.getName()) == 0);
    }
    SECTION("Removing owner")
    {
        Vehicle vehicle = Vehicle("C1234AB", "Lada");
        Person person = Person("Batman", 15);
        REQUIRE_FALSE(vehicle.isOwned());
        vehicle.addOwner(person);
        REQUIRE(vehicle.isOwned());
        vehicle.removeOwner();
        REQUIRE_FALSE(vehicle.isOwned());
        REQUIRE(&vehicle.getOwner() == nullptr);
    }
}
