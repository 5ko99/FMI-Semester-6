#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"

#include "Garage.h"

TEST_CASE("Initialization and copy of class Garage")
{
    Garage gar(7);
    Vehicle a("6969", "white smart", 1);
    Vehicle b("4200", "green truck", 3);
    Vehicle c("7777", "white van", 2);

    SECTION("Successfully creates class")
    {
        REQUIRE(gar.size() == 0);
    }

    SECTION("Copy constructor is operating correctly")
    {
        gar.insert(a);
        gar.insert(b);
        gar.insert(c);

        Garage copy(gar);

        REQUIRE(strcmp(copy[0].registration(), "6969") == 0);
        REQUIRE(strcmp(copy[0].description(), "white smart") == 0);
        REQUIRE(copy[0].space() == 1);

        REQUIRE(strcmp(copy[1].registration(), "4200") == 0);
        REQUIRE(strcmp(copy[1].description(), "green truck") == 0);
        REQUIRE(copy[1].space() == 3);
        REQUIRE(strcmp(copy[2].registration(), "4200") == 0);
        REQUIRE(strcmp(copy[2].description(), "green truck") == 0);
        REQUIRE(copy[2].space() == 3);
        REQUIRE(strcmp(copy[3].registration(), "4200") == 0);
        REQUIRE(strcmp(copy[3].description(), "green truck") == 0);
        REQUIRE(copy[3].space() == 3);

        REQUIRE(strcmp(copy[4].registration(), "7777") == 0);
        REQUIRE(strcmp(copy[4].description(), "white van") == 0);
        REQUIRE(copy[4].space() == 2);
        REQUIRE(strcmp(copy[5].registration(), "7777") == 0);
        REQUIRE(strcmp(copy[5].description(), "white van") == 0);
        REQUIRE(copy[5].space() == 2);
    }

    SECTION("Operator = is working properly")
    {
        gar.insert(a);
        gar.insert(b);
        gar.insert(c);

        Garage copy;
        copy = gar;

        REQUIRE(strcmp(copy[0].registration(), "6969") == 0);
        REQUIRE(strcmp(copy[0].description(), "white smart") == 0);
        REQUIRE(copy[0].space() == 1);

        REQUIRE(strcmp(copy[1].registration(), "4200") == 0);
        REQUIRE(strcmp(copy[1].description(), "green truck") == 0);
        REQUIRE(copy[1].space() == 3);
        REQUIRE(strcmp(copy[2].registration(), "4200") == 0);
        REQUIRE(strcmp(copy[2].description(), "green truck") == 0);
        REQUIRE(copy[2].space() == 3);
        REQUIRE(strcmp(copy[3].registration(), "4200") == 0);
        REQUIRE(strcmp(copy[3].description(), "green truck") == 0);
        REQUIRE(copy[3].space() == 3);

        REQUIRE(strcmp(copy[4].registration(), "7777") == 0);
        REQUIRE(strcmp(copy[4].description(), "white van") == 0);
        REQUIRE(copy[4].space() == 2);
        REQUIRE(strcmp(copy[5].registration(), "7777") == 0);
        REQUIRE(strcmp(copy[5].description(), "white van") == 0);
        REQUIRE(copy[5].space() == 2);
    }
}

TEST_CASE("Insert function")
{
    Garage gar(7);
    Vehicle a("6969", "white smart", 1);
    Vehicle b("4200", "green truck", 3);
    Vehicle c("7777", "white van", 2);
    Vehicle d("9999", "ferrari v cvyat cherven", 4);
    Vehicle e("4200", "green truck", 1);

    gar.insert(a);
    gar.insert(b);
    gar.insert(c);

    SECTION("If nothing is wrong")
    {
        REQUIRE(strcmp(gar[0].registration(), "6969") == 0);
        REQUIRE(strcmp(gar[0].description(), "white smart") == 0);
        REQUIRE(gar[0].space() == 1);

        REQUIRE(strcmp(gar[1].registration(), "4200") == 0);
        REQUIRE(strcmp(gar[1].description(), "green truck") == 0);
        REQUIRE(gar[1].space() == 3);
        REQUIRE(strcmp(gar[2].registration(), "4200") == 0);
        REQUIRE(strcmp(gar[2].description(), "green truck") == 0);
        REQUIRE(gar[2].space() == 3);
        REQUIRE(strcmp(gar[3].registration(), "4200") == 0);
        REQUIRE(strcmp(gar[3].description(), "green truck") == 0);
        REQUIRE(gar[3].space() == 3);

        REQUIRE(strcmp(gar[4].registration(), "7777") == 0);
        REQUIRE(strcmp(gar[4].description(), "white van") == 0);
        REQUIRE(gar[4].space() == 2);
        REQUIRE(strcmp(gar[5].registration(), "7777") == 0);
        REQUIRE(strcmp(gar[5].description(), "white van") == 0);
        REQUIRE(gar[5].space() == 2);
    }

    SECTION("Size is correct")
    {
        REQUIRE(gar.size() == 6);
    }

    SECTION("If there is not enough space")
    {
        REQUIRE_THROWS_AS(gar.insert(d), std::length_error);
    }

    SECTION("If there is already the same registry number")
    {
        REQUIRE_THROWS_AS(gar.insert(e), std::invalid_argument);
    }
}

TEST_CASE("Erase function is operaring correctly")
{
    Garage gar(7);
    Vehicle a("6969", "white smart", 1);
    Vehicle b("4200", "green truck", 3);
    Vehicle c("7777", "white van", 2);

    gar.insert(a);
    gar.insert(b);
    gar.insert(c);

    REQUIRE(gar.size() == 6);

    SECTION("If registration number exists - removing more than one")
    {
        gar.erase("4200");

        REQUIRE(strcmp(gar[0].registration(), "6969") == 0);
        REQUIRE(strcmp(gar[0].description(), "white smart") == 0);
        REQUIRE(gar[0].space() == 1);

        REQUIRE(strcmp(gar[1].registration(), "7777") == 0);
        REQUIRE(strcmp(gar[1].description(), "white van") == 0);
        REQUIRE(gar[1].space() == 2);
        REQUIRE(strcmp(gar[2].registration(), "7777") == 0);
        REQUIRE(strcmp(gar[2].description(), "white van") == 0);
        REQUIRE(gar[2].space() == 2);

        REQUIRE(gar.size() == 3);

        gar.erase("6969");

        REQUIRE(strcmp(gar[0].registration(), "7777") == 0);
        REQUIRE(strcmp(gar[0].description(), "white van") == 0);
        REQUIRE(gar[0].space() == 2);
        REQUIRE(strcmp(gar[1].registration(), "7777") == 0);
        REQUIRE(strcmp(gar[1].description(), "white van") == 0);
        REQUIRE(gar[1].space() == 2);

        REQUIRE(gar.size() == 2);
    }

    SECTION("If registration number exists - removing the last one")
    {
        gar.erase("7777");

        REQUIRE(strcmp(gar[0].registration(), "6969") == 0);
        REQUIRE(strcmp(gar[0].description(), "white smart") == 0);
        REQUIRE(gar[0].space() == 1);

        REQUIRE(strcmp(gar[1].registration(), "4200") == 0);
        REQUIRE(strcmp(gar[1].description(), "green truck") == 0);
        REQUIRE(gar[1].space() == 3);
        REQUIRE(strcmp(gar[2].registration(), "4200") == 0);
        REQUIRE(strcmp(gar[2].description(), "green truck") == 0);
        REQUIRE(gar[2].space() == 3);
        REQUIRE(strcmp(gar[3].registration(), "4200") == 0);
        REQUIRE(strcmp(gar[3].description(), "green truck") == 0);
        REQUIRE(gar[3].space() == 3);
    }

    SECTION("If registration number is not in the garage")
    {
        gar.erase("6000");

        REQUIRE(gar.size() == 6);
    }
}

TEST_CASE("At function behaviour when given wrong position, empty and clear func")
{
    Garage gar(7);
    Vehicle c("7777", "white van", 2);
    Vehicle v("1111", "white van", 2);

    SECTION("At function")
    {
        REQUIRE_THROWS_AS(gar.at(5), std::out_of_range);
    }

    SECTION("Empty function")
    {
        REQUIRE(gar.empty() == true);

        gar.insert(c);
        gar.insert(v);

        REQUIRE(gar.empty() == false);
    }

    SECTION("Empty function operating correctly")
    {
        gar.clear();

        REQUIRE(gar.size() == 0);
    }
}

TEST_CASE("Vehicle find function")
{
    Garage gar(7);
    Vehicle a("6969", "white smart", 1);
    Vehicle b("4200", "green truck", 3);
    Vehicle c("7777", "white van", 2);

    gar.insert(a);
    gar.insert(b);
    gar.insert(c);

    SECTION("If inpust is valid")
    {
        REQUIRE(gar.find("7777") == &c);
        REQUIRE(gar.find("6969") == &a);
        REQUIRE(gar.find("4200") == &b);
    }

    SECTION("If input is invalid")
    {
        REQUIRE(gar.find("5555") == nullptr);
    }
}
