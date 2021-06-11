//
// Created by Yani Drenchev on 18.05.21.
//
#include "../Source/Person.cpp"
#include "../Headers/Vehicle.h"
#include "single_include/catch2/catch.hpp"


TEST_CASE("person get ID valid tests", "[person id valid]") {
    Person p("Yani", 1);
    Person p2("Yani", 2);
    REQUIRE(p.getId() == 1);
    REQUIRE(p2.getId() != 1);
}

TEST_CASE("person get name valid tests", "[person name valid]") {
    Person p("Yani", 1);
    Person p2("Yani2", 2);
    REQUIRE(p.getName() == "Yani");
    REQUIRE(p2.getName() != "Yani");
}

TEST_CASE("person addVehicle valid tests", "[person addVehicle]") {
//    check if in the beginning the vector is empty
    Person p("Yani", 1);
    Registration registration1("ST1234ST");
    Registration registration2("ST1234TT");
    Registration registration3("ST1224TT");
    REQUIRE(p.getVehicles().empty());

    p.addVehicle(registration1);
    p.addVehicle(registration2);
    p.addVehicle(registration3);
//check if it is not empty and 3 vehicles are added
    REQUIRE(!p.getVehicles().empty());
    REQUIRE(p.getVehicles().size() == 3);
//check if duplicated vehicle is being added
//we can REQUIRE the function because it is boolean but this way is more readable.
    Registration registration4("ST1224TT");
    p.addVehicle(registration4);
    REQUIRE(p.getVehicles().size() == 3);
}


TEST_CASE("person remove valid tests", "[person remove]") {
//    check if in the beginning the vector is empty
    Person p("Yani", 1);
    Registration registration1("ST1234ST");
    Registration registration2("ST1234TT");
    Registration registration3("ST1224WT");
    p.addVehicle(registration1);
    p.addVehicle(registration2);
    p.addVehicle(registration3);
    REQUIRE(p.getVehicles().size() == 3);
//check if registration is removed
    p.removeVehicle(registration3);
    REQUIRE(p.getVehicles().size() == 2);
//check when an invalid number is being used
    p.removeVehicle(registration3);
    REQUIRE(p.getVehicles().size() == 2);
//    remove another one
    p.removeVehicle(registration1);
    REQUIRE(p.getVehicles().size() == 1);
}
