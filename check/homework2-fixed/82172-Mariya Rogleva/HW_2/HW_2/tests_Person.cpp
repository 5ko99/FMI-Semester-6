#include "catch2.hpp"
#include "Person.hpp"
#include "Vehicle.hpp"

TEST_CASE( "Creation", "[Person]" )
{
    Person test("Test Petrov", 12);

    SECTION("name and id")
    {
        REQUIRE(test.getName() == "Test Petrov");
        REQUIRE(test.getId() == 12);
    }
}

TEST_CASE( "Working with vehicles", "[Person]" )
{
    Person test("Test Petrov", 12);
    Registration reg("AB1234CD");
    Vehicle veh(reg, "Toyota");
    Registration reg1("XY1234AB"); //note that we don't expect any verifycations on this level
    Vehicle veh1(reg1, "Subaru");
    SECTION("1 vehicle")
    {
        REQUIRE(test.addVehicle(veh) == 1);
        REQUIRE(test.numberOfVehicles() == 1);
        
        REQUIRE(test.addVehicle(veh1) == 1); //add another vehicle
        REQUIRE(test.numberOfVehicles() == 2);

        REQUIRE(test.getVehicle(0)->getReg() == reg.getReg()); //get veh
        REQUIRE(test.getVehicle(1)->getReg() == reg1.getReg());
        REQUIRE_THROWS_AS(test.getVehicle(2), std::out_of_range);

        REQUIRE(test.releaseVehicle(reg) == 1); //remove veh
        REQUIRE(test.numberOfVehicles() == 1);
        REQUIRE(test.getVehicle(0)->getReg() == reg1.getReg());

        REQUIRE(test.releaseVehicle(reg) == 0); //remove last veh
        REQUIRE(test.releaseVehicle(reg1) == 1);
        REQUIRE(test.numberOfVehicles() == 0);
        REQUIRE_THROWS_AS(test.getVehicle(0), std::out_of_range);
    }
}
