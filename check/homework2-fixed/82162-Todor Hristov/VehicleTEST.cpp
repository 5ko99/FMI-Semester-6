#include "catch.h"
#include "Registration.h"
#include "Vehicle.h"
#include "Person.h"

#define CATCH_CONFIG_MAIN
TEST_CASE("Operator==InVehicle")
{
    Registration registration1("CA1234CA");
    Registration registration2("CA1234CA");
    Registration registration3("CA1235CA");
    Vehicle test1 (registration1, "nqkakvo opisanie");
    Vehicle test2 (registration2, "nqkakvo drugo opisanie");
    Vehicle test3 (registration3, "nqkakvo treto opisanie");
    bool isEqual = (test1 == test2);
    bool isNotEqual = (test1 == test3);
    REQUIRE(isEqual == 1);
    REQUIRE(isNotEqual == 0);
}
TEST_CASE("getRegistrationMethodInVehicle")
{
    Registration registration1("CA1234CA");
    Registration registration2("CA4321CA");
    Registration registration3("CA1235CA");
    Vehicle test1 (registration1, "nqkakvo opisanie");
    Vehicle test2 (registration2, "nqkakvo drugo opisanie");
    Vehicle test3 (registration3, "nqkakvo treto opisanie");
    bool isEqualtest1 = (test1.getRegistration() == registration1);
    bool isEqualtest2 = (test2.getRegistration() == registration2);
    bool isEqualtest3 = (test3.getRegistration() == registration3);
    REQUIRE(isEqualtest1 == 1);
    REQUIRE(isEqualtest2 == 1);
    REQUIRE(isEqualtest3 == 1);
}
TEST_CASE("getDescriptionMethodInVehicle")
{
    Registration registration1("CA1234CA");
    Registration registration2("CA4321CA");
    Registration registration3("CA1235CA");
    Vehicle test1 (registration1, "nqkakvo opisanie");
    Vehicle test2 (registration2, "nqkakvo drugo opisanie");
    Vehicle test3 (registration3, "nqkakvo treto opisanie");
    bool isEqualtest1 = (test1.getDescription() == "nqkakvo opisanie");
    bool isEqualtest2 = (test2.getDescription() == "nqkakvo drugo opisanie");
    bool isEqualtest3 = (test3.getDescription() == "nqkakvo treto opisanie");
    REQUIRE(isEqualtest1 == 1);
    REQUIRE(isEqualtest2 == 1);
    REQUIRE(isEqualtest3 == 1);
}
TEST_CASE("setOwnerInVehicle")
{
    Registration registration1("CA1234CA");
    Vehicle test1 (registration1, "nqkakvo opisanie");
    Person person1 ("pesho", 123);
    test1.setOwner(&person1);
    bool isEqualtest1 = (test1.getOwner() == &person1);
    REQUIRE(isEqualtest1 == 1);
}
TEST_CASE("clearOwnerInVehicle")
{
    Registration registration1("CA1234CA");
    Vehicle test1 (registration1, "nqkakvo opisanie");
    Person person1 ("pesho", 123);
    test1.setOwner(&person1);
    bool isEqualtest1 = (test1.getOwner() == &person1);
    REQUIRE(isEqualtest1 == 1);
    test1.clearOwner();
    isEqualtest1 = (test1.getOwner() == &person1);
    REQUIRE(isEqualtest1 == 0);
}
