//#define CATCH_CONFIG_MAIN
//used separate file test_main.cpp that should be compiled once 
//and then for compilation of vehicleallocator_unit_tests.cpp we should include test_main.o in the command
#include <iostream>
#include <cstring>
#include "../lib/catch.hpp"
#include "../include/vehicleallocator.hpp"
#include "../include/mystring.hpp"
#include "../include/vehicle.hpp"
#include "../include/garage.hpp"

TEST_CASE("Testing VehicleAllocator")
{
    Vehicle v1("1RT2", "Red Car", 2);
    Vehicle v2("6JF3", "Orange Bus", 4);
    Vehicle v3("A32U", "Small Car", 1);
    size_t garageCapacity = 5;
    Garage garage(garageCapacity);

    VehicleAllocator vehicles(garage);

    const Vehicle* res1 = &vehicles.allocate(v1.registration(), v1.description(), v1.space());
    const Vehicle* res2 = &vehicles.allocate(v2.registration(), v2.description(), v2.space());
    const Vehicle* res3 = &vehicles.allocate(v3.registration(), v3.description(), v3.space());

    REQUIRE(&vehicles[0] == res1);
    REQUIRE(&vehicles[1] == res2);
    REQUIRE(&vehicles[2] == res3);

    REQUIRE(strcmp(res1->registration(), v1.registration()) == 0);
    REQUIRE(strcmp(res1->description(), v1.description()) == 0);
    REQUIRE(res1->space() == v1.space());

    REQUIRE(strcmp(res2->registration(), v2.registration()) == 0);
    REQUIRE(strcmp(res2->description(), v2.description()) == 0);
    REQUIRE(res2->space() == v2.space());

    REQUIRE(strcmp(res3->registration(), v3.registration()) == 0);
    REQUIRE(strcmp(res3->description(), v3.description()) == 0);
    REQUIRE(res3->space() == v3.space());

    vehicles.add(0);//v1 added to the garage
    REQUIRE(garage.size() == 1);

    vehicles.add(2);
    REQUIRE(garage.size() == 2);
    REQUIRE(garage.find(v1.registration()) == &vehicles[0]);
    REQUIRE(garage.find(v3.registration()) == &vehicles[2]);

    vehicles.remove(0);//should remove the v1
    REQUIRE(garage.size() == 1);

    vehicles.remove(0);//should remove v3
    REQUIRE(garage.size() == 0);

    vehicles.add(1);
    REQUIRE(garage.size() == 1);
    REQUIRE(garage.find(v2.registration()) == &vehicles[1]);
    REQUIRE(garage.find(v1.registration()) == nullptr);
}