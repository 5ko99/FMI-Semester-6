#ifndef VEHICLETESTS_H
#define VEHICLETESTS_H
#include "catch2.hpp"
#include "../HW2/Vehicle.h"
#include "../HW2/Person.h"

TEST_CASE("Vehicle objects are created properly", "[Vehicle]")
{
    REQUIRE_NOTHROW(Vehicle("CA4242HG", "InfiniteImprobabilityDrive"));
    REQUIRE_THROWS(Vehicle("CA422HG", "InfiniteImprobabilityDrive"));
}

TEST_CASE("Primary methods work properly", "[Vehicle]")
{
    SECTION("Adding and removing an owner works correctly")
    {
        Person b("Emmet Brown", 191411);
        Vehicle a("HV4242CA", "DeLorean");
        a.addOwner(&b);
        REQUIRE(a.getOwnerId()==191411);
        REQUIRE_THROWS(a.addOwner(&b));
        a.removeOwner();
        REQUIRE(b.numberOfVehiclesOwned()==0);
        REQUIRE_THROWS(a.removeOwner());
    }
}

#endif
