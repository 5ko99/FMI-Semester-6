#define CATCH_CONFIG_MAIN
#include <string>
#include "catch2.hpp"
#include "registration.h"

TEST_CASE ("constructors, operator=, getLicensePlate") {

    Registration test, test2("A1234BC");
    Registration test3(test2), test4("BB9876AA");
    test4 = test;

    CHECK(test.getLicensePlate() == "N/A");
    CHECK(test2.getLicensePlate() == "A1234BC");
    CHECK(test3.getLicensePlate() == test2.getLicensePlate());
    CHECK(test4.getLicensePlate() == "N/A");
    
}

TEST_CASE ("setLicensePlate, operator==") {

    Registration test, test2("A1234AA");
    test.setLicensePlate("A1234AA");

    CHECK(test.getLicensePlate() == test2.getLicensePlate());
}
