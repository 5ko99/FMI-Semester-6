#include "catch2.hpp"
#include "../include/Vehicle.h"

TEST_CASE("Testing the registration parameter constructor")
{
    Registration reg("AH4545TH");

    REQUIRE(strcmp(reg.getNumber(), "AH4545TH") == 0);
}
TEST_CASE("Testing the registration copy constructor")
{
    Registration reg("AH4545TH");
    Registration reg2(reg);

    REQUIRE(strcmp(reg2.getNumber(), "AH4545TH") == 0);
}
TEST_CASE("Testing the registration =  and == operator")
{
    Registration reg("AH4545TH");
    Registration reg2 = reg;

    REQUIRE(strcmp(reg2.getNumber(), "AH4545TH") == 0);
    REQUIRE(reg == reg2);
}
