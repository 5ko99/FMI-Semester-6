#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"

#include "Vehicle.cpp"

TEST_CASE("Everything initializes correctly")
{
    const char *a = "CV6969KC";
    const char *b = "Orange with nyan cat wrap";
    std::size_t c = 1;
    Vehicle gtr(a, b, c);

    SECTION("Registration number")
    {
        REQUIRE(strcmp(gtr.registration(), a) == 0);
        REQUIRE(strcmp(gtr.description(), b) == 0);
        REQUIRE(gtr.space() == c);
    }
}