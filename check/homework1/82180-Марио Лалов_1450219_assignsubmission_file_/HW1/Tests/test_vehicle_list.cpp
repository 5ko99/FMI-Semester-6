#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../VehicleList/vehicle_list.h"

TEST_CASE("Vehicle list")
{
    VehicleList list;

    SECTION("test push and [] operator")
    {
        list.push("12345", "description", 3);

        Vehicle vehicle2("34567", "smth", 3);
        list.push("34567", "smth", 3);

        REQUIRE(vehicle2 == list[1]);
    }

    SECTION("test out of range exception operator[]")
    {
        list.push("12345", "description", 3);

        REQUIRE_THROWS_AS(list[2], std::out_of_range);
        REQUIRE_THROWS_AS(list[-1], std::out_of_range);
    }

    SECTION("test operator[] with empty")
    {
        REQUIRE_THROWS_AS(list[0], std::out_of_range);
    }

    SECTION("test get index")
    {
        list.push("12345", "description", 3);
        list.push("45678", "desc", 2);

        REQUIRE(list.getIndex("45678") == 1);
    }

    SECTION("test get index for non existent")
    {
        list.push("12345", "description", 3);
        list.push("45678", "desc", 2);

        REQUIRE(list.getIndex("45790") == -1);
    }

    SECTION("test get index for empty list")
    {
        REQUIRE(list.getIndex("00000") == -1);
    }

    SECTION("test remover")
    {
        list.push("12345", "description", 3);
        list.push("34567", "smth", 3);

        Vehicle vehicle3("7583", "desc", 4);
        list.push("7583", "desc", 4);

        list.remove("34567");

        REQUIRE(list[1] == vehicle3);
    }
}