#include "catch2.hpp"
#include "../include/Person.h"

TEST_CASE("Testing the person parameter constructor")
{
    Person p("Sonya", 82213);

    REQUIRE(p.getName() == "Sonya");
    REQUIRE(p.getId() == 82213);
}

TEST_CASE("Testing the  personcopy constructor")
{
    Person p("Sonya", 82213);
    Person p2(p);

    REQUIRE(p2.getName() == "Sonya");
    REQUIRE(p2.getId() == 82213);
}

TEST_CASE("Testing the person = operator")
{
    Person p("Sonya", 82213);
    Person p2 = p;

    REQUIRE(p2.getName() == "Sonya");
    REQUIRE(p2.getId() == 82213);
}

TEST_CASE("Testing the person == operator")
{
    Person p("Sonya", 82213);
    Person p2("Sonya", 82213);

    REQUIRE(p == p2);
}

TEST_CASE("Testing the person add vehicle function")
{
    Registration reg("VA4578OI");
    Person p("Sonya", 82213);
    Vehicle v(reg, "silver opel");

    p.addVehicle(&v);
    REQUIRE(p.cntOfVehicles() == 1);
}

TEST_CASE("Testing the  person remove vehicle function")
{
    Registration reg("VA4578OI");
    Person p("Sonya", 82213);
    Vehicle v(reg, "silver opel");

    p.addVehicle(&v);
    REQUIRE(p.cntOfVehicles() == 1);
    p.removeVehicle(&v);
    REQUIRE(p.cntOfVehicles() == 0);
}
TEST_CASE("Testing the person remove all vehicles function")
{
    Registration reg("VA4578OI");
    Registration reg2("SF4578OI");
    Person p("Sonya", 82213);
    Vehicle v(reg, "silver opel");
    Vehicle v2(reg2, "dark opel");

    p.addVehicle(&v);
    REQUIRE(p.cntOfVehicles() == 1);
    p.addVehicle(&v2);
    REQUIRE(p.cntOfVehicles() == 2);
    p.removeAllVehicles();
    REQUIRE(p.cntOfVehicles() == 0);
}
