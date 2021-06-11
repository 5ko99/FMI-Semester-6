#include <cstring>
#include <iostream>
#include "../lib/catch.hpp"
#include "../include/registration.h"
#include "../include/vehicle.h"

TEST_CASE("Testing person")
{
    string name = "Georgi Georgiev";
    unsigned long id = 12424;

    SECTION("Constructor")
    {
        Person person(name, id);

        REQUIRE(strcmp(person.getName(), name.c_str()) == 0);
        REQUIRE(person.getID() == id);
        REQUIRE(person.vehiclesCount() == 0);
    }

    SECTION("Methods")
    {
        Person p(name, id);
        Vehicle veh("C4242AB", "Great sport car");
        Vehicle veh2("DA4142DA", "Awesome description");

        REQUIRE(p.vehiclesCount() == 0);

        p.addVehicle(&veh);
        REQUIRE(p.vehiclesCount() == 1);
        REQUIRE(strcmp(p.getVehicleID(0),veh.getRegistration()) == 0);

        p.removeVehicle(&veh);
        REQUIRE(p.vehiclesCount() == 0);

        p.addVehicle(&veh);
        p.addVehicle(&veh);
        p.addVehicle(&veh2);
        REQUIRE(p.vehiclesCount() == 2);
        REQUIRE(strcmp(p.getVehicleID(1), veh2.getRegistration())==0);

        p.freeVehicles();
        REQUIRE(p.vehiclesCount() == 0);
        REQUIRE_THROWS_AS(p.getVehicleID(0), std::out_of_range);
    }
}
