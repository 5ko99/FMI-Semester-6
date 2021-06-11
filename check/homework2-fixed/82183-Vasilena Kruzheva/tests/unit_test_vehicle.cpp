#include <cstring>
#include <iostream>
#include "../lib/catch.hpp"
#include "../include/vehicle.h"
#include "../include/person.h"

TEST_CASE("Testing vehicle")
{
    Person p1("Ivan Ivanov", 124313);
    Person p2("Ivana Ivanova", 122551);

    Registration reg1("DA4224DA");
    Registration reg2("B2352KS");

    const char* descr1 = "Beautiful family car";
    const char* descr2 = "Beautiful sport car";

    SECTION("Constructors")
    {
        Vehicle v1(reg1.getRegistration(), descr1);
        Vehicle v2(reg2.getRegistration(), descr2, &p1);
        Vehicle v3(v2);

        REQUIRE(strcmp(v1.getRegistration(), reg1.getRegistration()) == 0);
        REQUIRE(strcmp(v1.getDescription(), descr1) == 0);
        REQUIRE(v1.getOwner() == nullptr);

        REQUIRE(strcmp(v2.getRegistration(), reg2.getRegistration()) == 0);
        REQUIRE(strcmp(v2.getDescription(), descr2) == 0);
        REQUIRE(v2.getOwner() == &p1);

        REQUIRE(strcmp(v2.getRegistration(), v3.getRegistration()) == 0);
        REQUIRE(strcmp(v2.getDescription(), v3.getDescription()) == 0);
        REQUIRE(v2.getOwner() == v3.getOwner());

        v3 = v1;

        REQUIRE(strcmp(v1.getRegistration(), v3.getRegistration()) == 0);
        REQUIRE(strcmp(v1.getDescription(), v3.getDescription()) == 0);
        REQUIRE(v1.getOwner() == v3.getOwner());
    }

    SECTION("Methods")
    {
        //One test section shouldn't rely on another
        p1.freeVehicles();
        p2.freeVehicles();

        Vehicle v1(reg1.getRegistration(), descr1);

        REQUIRE(v1.hasOwner() == false);

        v1.setOwner(&p1);
        REQUIRE(v1.hasOwner());
        REQUIRE(v1.getOwner() == &p1);
        
        REQUIRE(p1.vehiclesCount() == 1);
        REQUIRE(strcmp(p1.getVehicleID(0), v1.getRegistration()) == 0);

        v1.setOwner(&p2);
        REQUIRE(v1.hasOwner());
        REQUIRE(v1.getOwner() == &p2);
        REQUIRE(p2.vehiclesCount() == 1);
        REQUIRE(strcmp(p2.getVehicleID(0), v1.getRegistration()) == 0);
        
        REQUIRE(p1.vehiclesCount() == 0);
        REQUIRE_THROWS_AS(p1.getVehicleID(0), std::out_of_range);

        v1.release();
        REQUIRE(v1.hasOwner() == false);
        REQUIRE(v1.getOwner() == nullptr);
        REQUIRE(p2.vehiclesCount() == 0);
        REQUIRE_THROWS_AS(p2.getVehicleID(0), std::out_of_range);
    }
}
