#include "catch.h"
#include "MyString.h"
#include "Vehicle.h"
#define CATCH_CONFIG_MAIN

TEST_CASE("Registration_func")
{
    Vehicle test1("CA9876CA", "This is description", 3);
    REQUIRE (strcmp(test1.registration(),"CA9876CA") == 0);
}
TEST_CASE("Description_func")
 {
    Vehicle test1("CA9876CA", "This is description", 3);
    REQUIRE (strcmp(test1.description(),"This is description") == 0);
}
TEST_CASE("Space_func")
{
    Vehicle test1("CA9876CA", "This is description", 3);
    REQUIRE (test1.space() == 3);
}
