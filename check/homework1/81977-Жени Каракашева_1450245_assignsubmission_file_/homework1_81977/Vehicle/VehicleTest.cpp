#define CATCH_CONFIG_MAIN
#include "../catch2/catch2.hpp"
#include "Vehicle.h"

//to compile: g++ VehicleTest.cpp Vehicle.cpp ../MyString/MyString.cpp ../catch2/catch2.cpp
TEST_CASE ("Constructor test")
{
    SECTION("Testing constructor with parameters")
    {
        MyString registration("SB 2026");
        MyString description("BMW");

        Vehicle test(registration.c_str(),description.c_str(),3);

        REQUIRE(test.space() == 3);
        REQUIRE(strcmp(test.registration(), registration.c_str()) == 0); 
        REQUIRE(strcmp(test.description(), description.c_str()) == 0);

        MyString registrationTwo("H 2024 SB");
        MyString descriptionTwo("Mercedes");

        Vehicle testTwo(registrationTwo.c_str(), descriptionTwo.c_str(),5);

        REQUIRE(testTwo.space() == 5);
        REQUIRE(strcmp(testTwo.registration(), registrationTwo.c_str()) == 0); 
        REQUIRE(strcmp(testTwo.description(), descriptionTwo.c_str()) == 0);

    }

    
}