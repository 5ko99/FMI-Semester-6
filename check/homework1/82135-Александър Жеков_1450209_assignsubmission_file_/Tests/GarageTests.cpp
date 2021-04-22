#include "../HW1/Garage.h"
#include "../../catch2/include/catch.hpp"

TEST_CASE("Testing Garage constructors") {

    SECTION("Capacity constructor: ") {
        Garage grg(3);

        REQUIRE(grg.empty() == true);
        REQUIRE(grg.size() == 3);
    }

    SECTION("Garage copy constructor: ") {
        Vehicle vhc0("123456", "Red", 2);
        Vehicle vhc1("54321", "Blue", 2);

        Garage grg(5);
        grg.insert(vhc0);
        grg.insert(vhc1);
        Garage grgCopy(grg);

        REQUIRE(grgCopy.empty() == false);
        REQUIRE(grg.size() == grg.size());
        REQUIRE(grg.at(0).registration() == grgCopy.at(0).registration());
        REQUIRE(grg.at(0).description() == grgCopy.at(0).description());
        REQUIRE(grg.at(0).space() == grgCopy.at(0).space());
        REQUIRE(grg.at(1).registration() == grgCopy.at(1).registration());
        REQUIRE(grg.at(1).description() == grgCopy.at(1).description());
        REQUIRE(grg.at(1).space() == grgCopy.at(1).space());
    }

}

TEST_CASE("Testing Garage functions") {

    Garage grg(5);

    SECTION("Inserting Vehicle object with .insert(): ") {
        Vehicle vhc0("123456", "Red", 2);
        Vehicle vhc1("54321", "Green", 3);
        Vehicle vhc2("12321", "Blue", 4);

        grg.insert(vhc0);

        try {
            grg.insert(vhc0);
        }
        catch (const char* error) {
            REQUIRE(error == "Car with same registration is in the garage!");
        }

        grg.insert(vhc1);

        try {
            grg.insert(vhc2);
        }
        catch (const char* error) {
            REQUIRE(error == "Garage full!");
        }

        grg.erase("54321");

        try {
            grg.insert(vhc2);
        }
        catch (const char* error) {
            REQUIRE(error == "Not enough space for vehicle!");
        }
    }

    SECTION("Removing Vehicle object with .erase(): ") {
        Vehicle vhc0("123456", "Red", 2);
        Vehicle vhc1("54321", "Green", 3);

        grg.insert(vhc0);
        grg.insert(vhc1);

        grg.erase("54321");
        try {
            grg.erase("54321");
        }
        catch (const char* error) {
            REQUIRE(error == "No vehicle with such registration!");
        }
    }

    SECTION("Return Vehicle at index using .at(): ") {
        Vehicle vhc0("123456", "Red", 2);
        Vehicle vhc1("54321", "Green", 3);

        grg.insert(vhc0);
        grg.insert(vhc1);

        REQUIRE(grg.at(0).registration() == vhc0.registration());
        REQUIRE(grg.at(0).description() == vhc0.description());
        REQUIRE(grg.at(0).space() == vhc0.space());

        REQUIRE(grg.at(1).registration() == vhc1.registration());
        REQUIRE(grg.at(1).description() == vhc1.description());
        REQUIRE(grg.at(1).space() == vhc1.space());
    }

    SECTION("Check if Garage is empty using .empty(): ") {
        Vehicle vhc0("12345", "Red", 2);

        REQUIRE(grg.empty() == true);

        grg.insert(vhc0);

        REQUIRE(grg.empty() == false);

        grg.erase("12345");

        REQUIRE(grg.empty() == true);
    }

    SECTION("Check if Garage is full using .full(): ") {
        Vehicle vhc0("12345", "Red", 2);
        Vehicle vhc1("54321", "Blue", 3);

        REQUIRE(grg.isFull() == false);

        grg.insert(vhc0);

        REQUIRE(grg.isFull() == false);

        grg.insert(vhc1);

        REQUIRE(grg.isFull() == true);

        grg.erase("12345");

        REQUIRE(grg.isFull() == false);
    }

    SECTION("Return size of Garage using .size(): ") {
        Vehicle vhc0("12345", "Red", 2);
        Vehicle vhc1("54321", "Blue", 3);

        REQUIRE(grg.size() == 0);

        grg.insert(vhc0);

        REQUIRE(grg.size() == 1);

        grg.insert(vhc1);

        REQUIRE(grg.size() == 2);

        grg.erase("12345");

        REQUIRE(grg.size() == 1);

        grg.erase("54321");

        REQUIRE(grg.size() == 0);
    }

    SECTION("Remove all Vehicles from Garage using .clear(): ") {
        Vehicle vhc0("12345", "Red", 1);
        Vehicle vhc1("54321", "Blue", 1);
        Vehicle vhc2("12321", "Green", 1);
        Vehicle vhc3("32123", "Pink", 1);

        grg.insert(vhc0);
        grg.insert(vhc1);
        grg.insert(vhc2);
        grg.insert(vhc3);

        REQUIRE(grg.size() == 4);

        grg.clear();

        REQUIRE(grg.size() == 0);
    }

    SECTION("Return Vehicle by registration if its in the Garage using .find(): ") {
        Vehicle vhc0("12345", "Red", 2);
        Vehicle vhc1("54321", "Blue", 1);

        grg.insert(vhc0);

        REQUIRE(grg.find("12345")->registration() == "12345");
        REQUIRE(grg.find("12345")->description() == "Red");
        REQUIRE(grg.find("12345")->space() == 2);

        REQUIRE(grg.find("54321") == nullptr);
    }

}

TEST_CASE("Testing Garage operators") {

    Garage grg(5);

    SECTION("Index operator: ") {
        Vehicle veh0("12345", "Red", 2);
        Vehicle veh1("54321", "Blue", 3);

        grg.insert(veh0);
        grg.insert(veh1);

        REQUIRE(grg[0].registration() == "12345");
        REQUIRE(grg[0].description() == "Red");
        REQUIRE(grg[0].space() == 2);

        REQUIRE(grg[1].registration() == "54321");
        REQUIRE(grg[1].description() == "Blue");
        REQUIRE(grg[1].space() == 3);
    }

    SECTION("Copy assignment operator: ") {
        Vehicle veh0("12345", "Red", 2);
        Vehicle veh1("54321", "Blue", 3);

        grg.insert(veh0);
        grg.insert(veh1);

        Garage grgCopy = grg;

        REQUIRE(grgCopy.at(0).registration() == "12345");
        REQUIRE(grgCopy.at(0).description() == "Red");
        REQUIRE(grgCopy.at(0).space() == 2);

        REQUIRE(grgCopy.at(1).registration() == "54321");
        REQUIRE(grgCopy.at(1).description() == "Blue");
        REQUIRE(grgCopy.at(1).space() == 3);
    }

}