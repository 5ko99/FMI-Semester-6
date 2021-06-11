#include "catch_amalgamated.hpp"
#include "Registration.h"

TEST_CASE("General tests for Registration")
{
    SECTION("Default constructor")
    {
        Registration string;
        REQUIRE(string.isEmpty());
    }
    SECTION("Constructor that takes const char* as argument")
    {
        Registration string("C1234AB");
        REQUIRE(string.isEmpty() == false);
        REQUIRE(strcmp(string.getRegistration(), "C1234AB") == 0);
    }
    SECTION("Copy assignment constructor")
    {
        Registration first("XY1111YX");
        Registration second;
        second = first;
        REQUIRE(second.isEmpty() == false);
        REQUIRE(strcmp(second.getRegistration(), "XY1111YX") == 0);
    }
    SECTION("Test case for incorrect input")
    {
        Registration string("ABC34DEF");
        REQUIRE(string.isEmpty());
    }
    SECTION("Test for methods")
    {
        Registration string("ABC34DEF");
        REQUIRE(string.isEmpty());
        string.setRegistration("A1511KE");
        REQUIRE(strcmp(string.getRegistration(), "A1511KE") == 0);
    }
}
