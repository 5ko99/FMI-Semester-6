#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "vehicle.h"
#include "person.h"

TEST_CASE ("constructors, operator=, accessors. mutator") {

    const Registration licensePlate("A1111AA");
    Vehicle test, test1(licensePlate, "A vehicle.");
    Vehicle test3(test1);
   

    CHECK(test.getOwner() == nullptr);
    CHECK(test1.getLicensePlate() == licensePlate);
    CHECK(test3.getLicensePlate() == test1.getLicensePlate());

    test = test3;
    CHECK(test.getLicensePlate() == test3.getLicensePlate());

    Person person("Name", 1);

    test.setOwner(person);
    CHECK(test.getOwner() == &person);
}   
