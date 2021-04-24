#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "Garage.h"
#include "cstring"

TEST_CASE("Garage", "simple tests")
{
    SECTION("insert erase")
    {
        Vehicle veh1("reg1", "des1", 1);
        Vehicle veh2("reg2", "des2", 2);

        Garage gar(3);
        gar.insert(veh1);
        gar.insert(veh2);

        REQUIRE(gar.size() == 2);
        gar.insert(veh1);

        REQUIRE(gar.size() == 2);
        gar.erase("reg2");
        REQUIRE(gar.size() == 1);
    }

    SECTION("at []")
    {
        Vehicle veh1("reg1", "des1", 1);
        Vehicle veh2("reg2", "des2", 2);

        Garage gar(3);
        gar.insert(veh1);
        gar.insert(veh2);

        REQUIRE(strcmp(gar[0].registration(), "reg1") == 0);
        REQUIRE(strcmp(gar.at(1).description(), "des2") == 0);
    }

    SECTION("mischevous")
    {
        Vehicle veh1("reg1", "des1", 1);
        Vehicle veh2("reg2", "des2", 2);

        Garage gar(3);
        gar.insert(veh1);
        gar.insert(veh2);

        REQUIRE(gar.empty() == 0);
        REQUIRE(gar.size() == 2);
        gar.clear();
        REQUIRE(gar.empty() == 1);
    }

    SECTION("mischevous")
    {
        Vehicle veh1("reg1", "des1", 1);
        Vehicle veh2("reg2", "des2", 2);

        Garage gar(3);
        gar.insert(veh1);
        gar.insert(veh2);

        REQUIRE(gar.empty() == 0);
        REQUIRE(gar.size() == 2);
        gar.clear();
        REQUIRE(gar.empty() == 1);
    }

    SECTION("find")
    {
        Vehicle veh1("reg1", "des1" , 1);
        Vehicle veh2("reg2", "des2" , 2);

        Garage gar(3);
        gar.insert(veh1);
        gar.insert(veh2);

        REQUIRE(strcmp(gar.find("reg2")->description(), "des2" ) == 0 );
    }
}