#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Person/person.h"
#include "../Vehicle/vehicle.h"

TEST_CASE("constructor")
{
    SECTION("basic constructor test")
    {
        Person person1(1, "Pesho");

        REQUIRE(person1.getName() == "Pesho");
    }

    SECTION("used id error")
    {
        Person person1(1, "Pesho");
        REQUIRE_THROWS_AS(Person(1, "gosho"), std::invalid_argument);
    }
}

TEST_CASE("owning and disowning vehicles")
{
    Person person1(1, "Pesho");

    Vehicle vehcile1("CA1234XX", "desc");
    Vehicle vehcile2("AA1222XX", "desc");
    Vehicle vehcile3("HJ1444XX", "desc");

    REQUIRE(!vehcile1.getOwner());

    person1.addVehicle(&vehcile2);
    person1.addVehicle(&vehcile1);
    person1.addVehicle(&vehcile3);

    REQUIRE(vehcile1.getOwner() == &person1);

    person1.disownVehicle("CA1234XX");

    REQUIRE(!vehcile1.checkIfOwned());
    REQUIRE(vehcile2.checkIfOwned());
    REQUIRE(vehcile3.checkIfOwned());
}

TEST_CASE("getters")
{
    Person person1(1, "Pesho");

    SECTION("person related getters")
    {
        REQUIRE(person1.getId() == 1);
        REQUIRE(person1.getName() == "Pesho");
    }

    Vehicle vehcile1("CA1234XX", "desc");
    Vehicle vehcile2("AA1222XX", "desc");
    Vehicle vehcile3("HJ1444XX", "desc");

    person1.addVehicle(&vehcile2);
    person1.addVehicle(&vehcile1);
    person1.addVehicle(&vehcile3);

    SECTION("vehicle related getters")
    {
        REQUIRE(person1.getVehicleIndex("CA1234XX") == 1);
        REQUIRE(person1.getVehicleByRegistration("CA1234XX") == &vehcile1);
    }
}
