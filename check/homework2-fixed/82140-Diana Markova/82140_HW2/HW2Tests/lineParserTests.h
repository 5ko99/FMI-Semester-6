#ifndef LINEPARSERTESTS_H
#define LINEPARSERTESTS_H
#include "catch2.hpp"
#include "../HW2/lineParser.h"
#include <string>
#include <cstring>

TEST_CASE("Parser parses correctly", "[lineParser]")
{
    lineParser lp;
    lp.parseLine("   hello \" some text asasd\" \"more text\" lordOftheRings    ");
    REQUIRE(std::strcmp(lp.command(),"hello")==0);
    REQUIRE(lp.arguments()[0]==" some text asasd");
    REQUIRE(lp.arguments()[1]=="more text");
    REQUIRE(lp.arguments()[2]=="lordOftheRings");
}


#endif // LINEPARSERTESTS_H
