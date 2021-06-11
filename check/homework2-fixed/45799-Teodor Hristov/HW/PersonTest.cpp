#include <iostream>
#include "catch_amalgamated.hpp"
#include "Registration.h"
#include "Person.h"
#include "Vehicle.h"

TEST_CASE("addVehicle nullptr test"){
    Person p("Hristo", 0);
    REQUIRE_THROWS(p.addVehicle(nullptr));
}

TEST_CASE("addVehicle valid input"){
    Person p("Hristo", 0);
    Registration r("CA1234AV");
    Vehicle v(&r, "test desc");

    REQUIRE_NOTHROW(p.addVehicle(&v));
    REQUIRE(p.getVehicles()[0]);
}

TEST_CASE("removeVehicle nullptr test"){
    Person p("Hristo", 0);
    REQUIRE_THROWS(p.addVehicle(nullptr));
}

TEST_CASE("removeVehicle valid input"){
    Person p("Hristo", 0);
    Registration r("CA1234AV");
    Vehicle v(&r, "test desc");
    p.addVehicle(&v);
    REQUIRE_NOTHROW(p.removeVehicle(&v));
    REQUIRE(p.getVehicles().size() == 0);
}

TEST_CASE("id exists with nullptr"){
    REQUIRE_THROWS(Person::idExists(0, nullptr));
}
