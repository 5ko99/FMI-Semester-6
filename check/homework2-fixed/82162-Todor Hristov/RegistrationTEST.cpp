#include "catch.h"
#include "Registration.h"
#define CATCH_CONFIG_MAIN
TEST_CASE("Operator==InRegistration")
{
    Registration test1("CA1234CA");
    Registration test2("CA1234CA");
    Registration test3("CA1235CA");
    bool isEqual = (test1 == test2);
    bool isNotEqual = (test1 == test3);
    REQUIRE(isEqual == 1);
    REQUIRE(isNotEqual == 0);
}
TEST_CASE("getMethodInRegistration")
{
    Registration test1("CA1234CA");
    Registration test2("CA1234CA");
    Registration test3("CA1235CA");
    REQUIRE(test1.getRegistration() == "CA1234CA");
    REQUIRE(test2.getRegistration() == "CA1234CA");
    REQUIRE(test3.getRegistration() == "CA1235CA");
}
