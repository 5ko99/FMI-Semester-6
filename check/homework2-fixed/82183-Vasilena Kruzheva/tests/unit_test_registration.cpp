#include <cstring>
#include <iostream>
#include "../lib/catch.hpp"
#include "../include/registration.h"

TEST_CASE("Testing registration")
{
    const char* arr1 = "CR1234AB";
    const char* arr2 = "W1243FA";

    SECTION("Constructor")
    {
        Registration reg1(arr1);
        REQUIRE(strcmp(reg1.getRegistration(), arr1) == 0);

        Registration reg2(arr2);
        REQUIRE(strcmp(reg2.getRegistration(), arr2) == 0);

        Registration reg3(reg1);
        REQUIRE(strcmp(reg1.getRegistration(), reg3.getRegistration()) == 0);

        reg3 = reg2;
        REQUIRE(strcmp(reg2.getRegistration(), reg3.getRegistration()) == 0);
    }

    SECTION("Invalid arguments")
    {
        try
        {
            Registration r("111145");
        }
        catch(const std::invalid_argument& e)
        {
            REQUIRE(strcmp(e.what(), "Invalid registration number") == 0);
        }

        try
        {
            Registration r("ABC34DEF");
        }
        catch(const std::invalid_argument& e)
        {
            REQUIRE(strcmp(e.what(), "Invalid registration number") == 0);
        }

        try
        {
            Registration r("ABCDEF");
        }
        catch(const std::invalid_argument& e)
        {
            REQUIRE(strcmp(e.what(), "Invalid registration number") == 0);
        }

        try
        {
            Registration r("C12345B");
        }
        catch(const std::invalid_argument& e)
        {
            REQUIRE(strcmp(e.what(), "Invalid registration number") == 0);
        }

        try
        {
            Registration r("a7777GR");
        }
        catch(const std::invalid_argument& e)
        {
            REQUIRE(strcmp(e.what(), "Invalid registration number") == 0);
        }
    }
}
