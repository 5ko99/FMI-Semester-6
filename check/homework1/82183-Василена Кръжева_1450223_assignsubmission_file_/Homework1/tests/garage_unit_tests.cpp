//#define CATCH_CONFIG_MAIN
//used separate file test_main.cpp that should be compiled once 
//and then for compilation of garage_unit_tests.cpp we should include test_main.o in the command
#include <iostream>
#include <cstring>
#include "../lib/catch.hpp"
#include "../include//mystring.hpp"
#include "../include//vehicle.hpp"
#include "../include//garage.hpp"

TEST_CASE("Testing constructors")
{
    Vehicle v1("1RT2", "Red Car", 2);
    Vehicle v2("6JF3", "Orange Bus", 4);
    Vehicle v3("A32U", "Small Car", 1);

    SECTION("Constructor taking size")
    {
        Garage garage(5);
        garage.insert(v1);

        REQUIRE(garage.size() == 1);
        REQUIRE_THROWS_AS(garage.insert(v2), std::length_error);
        REQUIRE(strcmp(garage.find(v1.registration())->description(),v1.description())==0);
    }

    SECTION("Constructor taking another garage")
    {
        Garage garage(3);
        garage.insert(v1);
        garage.insert(v3);

        Garage garage2(garage);

        REQUIRE(garage2.size() == garage.size());

        for (size_t i = 0; i < garage.size(); i++)
        {
            REQUIRE(strcmp(garage2.at(i).registration(),garage.at(i).registration()) == 0);
            REQUIRE(strcmp(garage2.at(i).description(),garage.at(i).description()) == 0);
            REQUIRE(garage2.at(i).description() == garage.at(i).description());
        }
    }
}

TEST_CASE("Overloaded operator =")
{
    Vehicle v1("1RT2", "Red Car", 2);
    Vehicle v2("6JF3", "Orange Bus", 4);

    Garage garage(6);
    garage.insert(v1);
    garage.insert(v2);

    Garage garage2(3);
    garage2 = garage;

    REQUIRE(garage2.size() == garage.size());

    for (size_t i = 0; i < garage.size(); i++)
    {
        REQUIRE(strcmp(garage2.at(i).registration(),garage.at(i).registration()) == 0);
        REQUIRE(strcmp(garage2.at(i).description(),garage.at(i).description()) == 0);
        REQUIRE(garage2.at(i).space() == garage.at(i).space());
    }
}

TEST_CASE("Testing other garage functions")
{
    Vehicle v1("1RT2", "Red Car", 2);
    Vehicle v2("6JF3", "Orange Bus", 4);
    Vehicle v3("A32U", "Small Car", 1);
    
    Garage garage(5);

    SECTION("Insert Vehicle function")
    {
        garage.insert(v1);

        REQUIRE(garage.size() == 1);

        REQUIRE(strcmp(garage.at(0).registration(), v1.registration()) == 0);
        REQUIRE(strcmp(garage.at(0).description(), v1.description()) == 0);
        REQUIRE(garage.at(0).space() == v1.space());

        REQUIRE_THROWS_AS(garage.insert(v1), std::invalid_argument);
        REQUIRE_THROWS_AS(garage.insert(v2), std::length_error);
    }

    SECTION("Erase Vehicle function")
    {
        garage.clear();

        garage.insert(v2);
        REQUIRE(garage.size() == 1);

        garage.insert(v3);
        REQUIRE(garage.size() == 2);

        garage.erase(v2.registration());
        REQUIRE(garage.size() == 1);

        garage.erase(v3.registration());
        REQUIRE(garage.size() == 0);
        REQUIRE(garage.empty() == true);
    }

    SECTION("Testing function at(pos)")
    {
        garage.clear();
        REQUIRE_THROWS_AS(garage.at(0), std::out_of_range);

        garage.insert(v1);
        REQUIRE(strcmp(garage.at(0).registration(), v1.registration()) == 0);
        REQUIRE(strcmp(garage.at(0).description(), v1.description()) == 0);
        REQUIRE(garage.at(0).space() == v1.space());

        garage.insert(v3);
        REQUIRE(strcmp(garage.at(1).registration(), v3.registration()) == 0);
        REQUIRE(strcmp(garage.at(1).description(), v3.description()) == 0);
        REQUIRE(garage.at(1).space() == v3.space());
    }

    SECTION("Testing operator[]")
    {
        garage.clear();
        garage.insert(v2);
        
        REQUIRE(strcmp(garage[0].registration(), v2.registration()) == 0);
        REQUIRE(strcmp(garage[0].description(), v2.description()) == 0);
        REQUIRE(garage[0].space() == v2.space());
    }

    SECTION("Testing empty function")
    {
        garage.clear();
        REQUIRE(garage.empty() == true);

        garage.insert(v1);
        REQUIRE(garage.empty() == false);
    }

    SECTION("Testing find function")
    {
        garage.clear();
        REQUIRE(garage.find(v1.registration()) == nullptr);

        garage.insert(v1);
        garage.insert(v3);
        const Vehicle* found = garage.find(v3.registration());

        REQUIRE(strcmp(found->registration(), v3.registration()) == 0);
        REQUIRE(strcmp(found->description(), v3.description()) == 0);
        REQUIRE(found->space() == v3.space());
        REQUIRE(garage.size() == 2);
    }
}