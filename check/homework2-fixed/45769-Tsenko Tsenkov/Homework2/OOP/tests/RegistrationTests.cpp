#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../include/Registration.hpp"

using std::string;
string regNum = "InvalidNumber";

TEST_CASE("Invalid registration number", "[Registration]")
{
    CHECK_THROWS(Registration(regNum));
    regNum = "CA12345BC";
    CHECK_THROWS(Registration(regNum));
    regNum = "C1234BC";
    CHECK_THROWS(Registration(regNum));
    regNum = "ca1234bc";
    CHECK_THROWS(Registration(regNum));
    regNum = "CA1234B";
    CHECK_THROWS(Registration(regNum));
}

TEST_CASE("Valid registration number", "[Registration]")
{
    regNum = "CA1234BC";
    CHECK_NOTHROW(Registration(regNum));
    regNum = "AZ0000ZC";
    Registration registration(regNum);
    REQUIRE("AZ0000ZC" == registration.getRegistration());
}

TEST_CASE("Unique registration number", "[Registration]")
{
    CHECK_THROWS(Registration(regNum));
    regNum = "AB0000ZC";
    CHECK_NOTHROW(Registration(regNum));
}
