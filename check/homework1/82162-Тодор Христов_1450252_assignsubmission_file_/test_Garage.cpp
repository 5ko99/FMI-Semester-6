#include "catch.h"
#include "MyString.h"
#include "Vehicle.h"
#include "Garage.h"
#define CATCH_CONFIG_MAIN

TEST_CASE("Insert_func")
{
    Garage test1(15);
    SECTION("testes with greater size") {
        Vehicle vehicle1("CA9876CA", "This is description", 100);
        REQUIRE_THROWS_AS(test1.insert(vehicle1), std::exception);
    }
    Vehicle vehicle2("CA9876CA", "This is description", 3);
    test1.insert(vehicle2);
    REQUIRE(test1.size() == 1);
    Vehicle vehicle3("CA9874CA", "This is description", 3);
    test1.insert(vehicle3);
    REQUIRE(test1.size() == 2);
}

TEST_CASE("Erase_func")
{
    Garage test1(15);
    SECTION("testes with unknown registration") {
        REQUIRE_THROWS_AS(test1.erase("CA9876CA"), std::exception);
    }
    Vehicle vehicle1("CA9876CA", "This is description", 3);
    Vehicle vehicle2("CA9875CA", "This is description", 4);
    Vehicle vehicle3("CA9874CA", "This is description", 5);
    test1.insert(vehicle1);
    test1.insert(vehicle2);
    test1.insert(vehicle3);
    REQUIRE(test1.size() == 3);
    test1.erase("CA9874CA");
    REQUIRE(test1.size() == 2);
    REQUIRE_THROWS_AS(test1.erase("CA9874CA"), std::exception);
}
TEST_CASE("At_func")
{
    Garage test1(15);
    SECTION("testes with wrong pos") {
        Vehicle vehicle1("CA9876CA", "This is description", 3);
        test1.insert(vehicle1);
        REQUIRE_THROWS_AS(test1.at(6), std::exception);
    }
}

TEST_CASE("Empty_func")
{
    Garage test1(15);
    REQUIRE(test1.empty() == 1);
    Vehicle vehicle1("CA9876CA", "This is description", 3);
    test1.insert(vehicle1);
    REQUIRE(test1.empty() == 0);
}
TEST_CASE("Size_func")
{
    Garage test1(15);
    REQUIRE(test1.size() == 0);
    Vehicle vehicle2("CA9876CA", "This is description", 3);
    test1.insert(vehicle2);
    REQUIRE(test1.size() == 1);
    Vehicle vehicle3("CA9874CA", "This is description", 3);
    test1.insert(vehicle3);
    REQUIRE(test1.size() == 2);
    test1.erase("CA9874CA");
    REQUIRE(test1.size() == 1);
}
TEST_CASE("Clear_func")
{
    Garage test1(15);
    Vehicle vehicle2("CA9876CA", "This is description", 3);
    test1.insert(vehicle2);
    Vehicle vehicle3("CA9874CA", "This is description", 3);
    test1.insert(vehicle3);
    REQUIRE(test1.size() == 2);
    test1.clear();
    REQUIRE(test1.size() == 0);
}
TEST_CASE("Find_func")
{
    Garage test1(15);
    Vehicle vehicle2("CA9876CA", "This is description", 3);
    test1.insert(vehicle2);
    Vehicle vehicle3("CA9874CA", "This is description", 3);
    test1.insert(vehicle3);
    REQUIRE(test1.find("CaCa") == 0);
}
