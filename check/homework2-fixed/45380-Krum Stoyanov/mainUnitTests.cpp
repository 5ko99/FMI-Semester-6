#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "hw2.h"


TEST_CASE(" Testing operator == for Registration type", "[operator ==]")
{
    Registration a("qwerty");
    Registration b("qwerty");
    Registration c("qwertyyyy");
    REQUIRE(a == b);
    REQUIRE( !(a == c) );
    REQUIRE( !(b == c) );

}


TEST_CASE(" ", "[add_car,is_exist_car]")
{
    Person p;
    Registration r("S2076TR");
    Vehicle s(r,"-",45);
    p.add_car(s);
    REQUIRE(p.is_exist_car(s));

}
TEST_CASE(" Testing validation of registratin ", "[valid_reg]")
{
    InformationBase t;
    REQUIRE(t.valid_reg("C1234AB"));
    REQUIRE(t.valid_reg("XY1111YX"));
    REQUIRE(!t.valid_reg("111145"));
    REQUIRE(!t.valid_reg("ABCDEF"));
    REQUIRE(!t.valid_reg("ABC34DEF"));

}

