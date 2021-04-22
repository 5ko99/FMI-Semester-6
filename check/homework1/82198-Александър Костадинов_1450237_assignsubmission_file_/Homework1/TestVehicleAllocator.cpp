#include "catch2.hpp"
#include "VehicleAllocator.h"

TEST_CASE("Set_size Testing")
{
    VehicleAllocator v1;
    VehicleAllocator v2;
    VehicleAllocator v3;

    v1.set_size(5);
    v2.set_size(10);
    v3.set_size(0);

    REQUIRE(v1.get_size() == 5);
    REQUIRE(v2.get_size() == 10);
    REQUIRE(v3.get_size() == 0);
}

TEST_CASE("Allocate and Operator[] Testing")
{
    //Аllocate all
    VehicleAllocator v1;
    VehicleAllocator v2;

    Vehicle vehicle1("1", "A", 2);
    Vehicle vehicle2("2", "B", 2);
    Vehicle vehicle3("3", "C", 2);
    Vehicle vehicle4("4", "D", 2);
    Vehicle vehicle5("5", "E", 2);

    v1.set_size(2);
    v2.set_size(3);

    v1.allocate();
    v2.allocate();

    REQUIRE(v1[0].get_description() == vehicle1.get_description());
    REQUIRE(v1[1].get_registration() == vehicle2.get_registration());
    REQUIRE(v2[0].get_space() == vehicle3.get_space());
    REQUIRE(v2[1].get_description() == vehicle4.get_description());
    REQUIRE(v2[2].get_registration() == vehicle5.get_registration());
}

