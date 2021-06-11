#ifndef PERSONTESTS_H
#define PERSONTESTS_H
#include "../HW2/Person.h"
#include "../HW2/Vehicle.h"
#include "catch2.hpp"

TEST_CASE("Person objects are created properly", "[Person]")
{
    REQUIRE_NOTHROW(Person("John Arbuckle", 6492));
}

TEST_CASE("Side methods work properly for Person", "[Person]")
{
    SECTION("Adding a vehicle works correctly")
    {
        ///What happens here is analogous to what happens in Vehicle
        ///Namely because Person 'leaks' its components to Vehicle
        Vehicle a("HV4242CA", "DeLorean");
        Vehicle c("X1234YZ", "someKindOfVehicle");
        Person p("Emmet Brown", 191455);
        p.acquire(&a);
        REQUIRE(p.numberOfVehiclesOwned()==1);
        REQUIRE_NOTHROW(p.acquire(&a));
        REQUIRE(p.numberOfVehiclesOwned()==1);
        p.acquire(&c);
        REQUIRE(p.numberOfVehiclesOwned()==2);
    }
    SECTION("Releasing a vehicle works correctly")
    {
        Vehicle a("HV4242CA", "DeLorean");
        Vehicle c("X1234YZ", "someKindOfVehicle");
        Person p("Emmet Brown", 191455);
        p.acquire(&a);
        REQUIRE(p.numberOfVehiclesOwned()==1);
        p.acquire(&c);
        REQUIRE(p.numberOfVehiclesOwned()==2);
        p.release(&a);
        REQUIRE(p.numberOfVehiclesOwned()==1);
        p.release(&c);
        REQUIRE(p.numberOfVehiclesOwned()==0);
        REQUIRE_THROWS(p.release(&a));
        REQUIRE(p.numberOfVehiclesOwned()==0);
    }
}

#endif
