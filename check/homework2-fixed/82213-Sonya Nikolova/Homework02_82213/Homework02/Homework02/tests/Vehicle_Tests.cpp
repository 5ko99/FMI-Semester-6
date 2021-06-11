#include "catch2.hpp"
#include "../include/Vehicle.h"

TEST_CASE("Testing the vehicle parameter constructor")
{
    Registration reg("ER7836OK");
    Vehicle v(reg, "dark opel");
    REQUIRE(strcmp(v.getRegistration().getNumber(), "ER7836OK") == 0);
    REQUIRE(v.getDescription() == "dark opel");
}

TEST_CASE("Testing the vehicle copy constructor")
{
    Registration reg("ER7836OK");
    Vehicle v(reg, "dark opel");
    Vehicle v2(v);

    REQUIRE(strcmp(v2.getRegistration().getNumber(), "ER7836OK") == 0);
    REQUIRE(v2.getDescription() == "dark opel");
}

TEST_CASE("Testing the vehicle = operator")
{
    Registration reg("ER7836OK");
    Vehicle v(reg, "dark opel");
    Vehicle v2 = v;

    REQUIRE(strcmp(v2.getRegistration().getNumber(), "ER7836OK") == 0);
    REQUIRE(v2.getDescription() == "dark opel");
}

TEST_CASE("Testing the vehicle == operator")
{
    Registration reg("ER7836OK");
    Vehicle v(reg, "dark opel");
    Vehicle v2 = v;

    REQUIRE(v2 == v);
}

TEST_CASE("Testing the vehicle set and clear owner functions")
{

    Registration reg("ER7836OK");
    Vehicle v(reg, "dark opel");
    Person p("Ivan", 14);
    v.setOwner(p);
    REQUIRE(v.getOwner() == &p);
    v.clearOwner();
    REQUIRE(v.getOwner() == nullptr);

}
