#define CATCH_CONFIG_MAIN 
#include "catch2.hpp"
#include "Program.h"

TEST_CASE("Registration")
{
    Registration r("SA1111KK");
    CHECK(r.valid_symbol());
}

TEST_CASE("Vehicle")
{
    Registration r("SA1111KK");
    CHECK(r.valid_symbol());
    Vehicle v(r,"A car");

    CHECK(r.valid_symbol());
    CHECK(v.getDetails() == "A car");
}

TEST_CASE("Person")
{
    Person p("Todor", 5);
    CHECK(p.getName() == "Todor");
    CHECK(p.getID() == 5);
}


