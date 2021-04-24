#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "Vehicle.h"
#include "cstring"

TEST_CASE("Vehicles", "simple tests")
{
    const char *registration = {"reg"};
    const char *description  = {"des"};
    std::size_t space = 2;
    Vehicle one(registration, description, space);

    size_t i = 0;
    while(one.registration()[i])
    {
        REQUIRE(registration[i] == one.registration()[i] );
        i++;
    }
    i = 0;
    while(one.description()[i])
    {

        REQUIRE(description[i] == one.description()[i]);
        i++;
    }
    REQUIRE(space == one.space());

}



