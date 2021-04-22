//#define CATCH_CONFIG_MAIN
//used separate file test_main.cpp that should be compiled once 
//and then for compilation of vehicle_unit_tests.cpp we should include test_main.o in the command
#include <iostream>
#include <cstring>
#include "../lib/catch.hpp"
#include "../include//mystring.hpp"
#include "../include//vehicle.hpp"

TEST_CASE("Constructor")
{
    char reg[] = "0RE1";
    char descr[] = "Red Car";
    size_t park_space = 2;

    Vehicle v(reg, descr, park_space);
    REQUIRE(strcmp(v.registration(), reg) == 0);
    REQUIRE(strcmp(v.description(), descr) == 0);
    REQUIRE(v.space() == park_space);
} 