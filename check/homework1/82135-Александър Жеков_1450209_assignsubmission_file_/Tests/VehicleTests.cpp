#include "../HW1/Vehicle.h"
#include "../../catch2/include/catch.hpp"

TEST_CASE("Testing Vehicle constructors") {

    SECTION("Parameterized constructor: ") {
        Vehicle vhc1("123456", "Red", 2);
        Vehicle vhc2(nullptr, "Blue", 3);
        Vehicle vhc3("654321", nullptr, 2);
        Vehicle vhc4(nullptr, nullptr, 0);

        REQUIRE(vhc1.registration() == "123456");
        REQUIRE(vhc1.description() == "Red");
        REQUIRE(vhc1.space() == 2);

        REQUIRE(vhc2.registration() == "No registration");
        REQUIRE(vhc2.description() == "Blue");
        REQUIRE(vhc2.space() == 3);

        REQUIRE(vhc3.registration() == "654321");
        REQUIRE(vhc3.description() == "No description");
        REQUIRE(vhc3.space() == 2);

        REQUIRE(vhc4.registration() == "No registration");
        REQUIRE(vhc4.description() == "No description");
        REQUIRE(vhc4.space() == 1);
    }

    SECTION("Vehicle copy constructor: ") {
        Vehicle vhc0("123456", "Red", 2);
        Vehicle vhc1(vhc0);

        Vehicle vhc2(nullptr, nullptr, 0);
        Vehicle vhc3(vhc2);

        REQUIRE(vhc1.registration() == "123456");
        REQUIRE(vhc1.description() == "Red");
        REQUIRE(vhc1.space() == 2);

        REQUIRE(vhc3.registration() == "No registration");
        REQUIRE(vhc3.description() == "No description");
        REQUIRE(vhc3.space() == 1);
    }

}

TEST_CASE("Testing Vehicle class functions") {

    SECTION("regNum getter: ") {
        Vehicle vhc1("123456", "Red", 2);
        Vehicle vhc2(nullptr, "Blue", 3);

        REQUIRE(vhc1.registration() == "123456");
        REQUIRE(vhc2.registration() == "No registration");
    }

    SECTION("Descr getter: ") {
        Vehicle vhc1("123456", "Red", 2);
        Vehicle vhc2("654321", nullptr, 6);

        REQUIRE(vhc1.description() == "Red");
        REQUIRE(vhc2.description() == "No description");
    }

    SECTION("parkSpots getter: ") {
        Vehicle vhc1("123456", "Red", 2);
        Vehicle vhc2("654321", "Blue", 0);

        REQUIRE(vhc1.space() == 1);
    }

}