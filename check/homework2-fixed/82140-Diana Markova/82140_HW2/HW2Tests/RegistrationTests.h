#ifndef REGISTRATIONTESTS_H
#define REGISTRATIONTESTS_H
#include "catch2.hpp"
#include "../HW2/Registration.h"

TEST_CASE("Registration objects are created and rules are satisfied", "[Registration]")
{
    SECTION("Registration objects which should be acceptable")
    {
        REQUIRE_NOTHROW(Registration("CA2569WS"));
        REQUIRE_NOTHROW(Registration("W0000SM"));
    }
    SECTION("Registration objects which should be unacceptable")
    {
        REQUIRE_THROWS(Registration("0W000MH"));
        REQUIRE_THROWS(Registration("W000MH0"));
        REQUIRE_THROWS(Registration("CA2569WS0"));
        REQUIRE_THROWS(Registration("CA25609WS"));
        REQUIRE_THROWS(Registration("C22569WS"));
        REQUIRE_THROWS(Registration("C2569W0S"));
        REQUIRE_THROWS(Registration(""));
    }
}

TEST_CASE("Side methods work properly", "[Registration]")
{
    Registration a("CA2569WS");
    Registration b("CA2569WS");
    Registration c("CA2568WS");
    REQUIRE(a==b);
    REQUIRE(!(a==c));
}

#endif
