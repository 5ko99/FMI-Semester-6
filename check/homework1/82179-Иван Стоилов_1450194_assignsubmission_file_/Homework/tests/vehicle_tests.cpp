#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "..\Vehicle\vehicle.hpp"

TEST_CASE("vehicle")
{
    //constructor tests
    SECTION("testing constructor license plate")
    {
        char licensePlate[10] = "X 0853 KP";
        char vehicleDescription[14] = "BMW E91 330xd";
        size_t parkLots = 1;

        Vehicle testVehcile(licensePlate, vehicleDescription, parkLots);

        const char *testVehicleLicensePlate = testVehcile.registration();

        for (size_t counter = 0; counter < 9; ++counter)
        {
            REQUIRE(testVehicleLicensePlate[counter] == licensePlate[counter]);
        }  
    }

    SECTION("testing constructor vehicle description")
    {
        char licensePlate[10] = "X 0853 KP";
        char vehicleDescription[14] = "BMW E91 330xd";
        size_t parkLots = 1;

        Vehicle testVehcile(licensePlate, vehicleDescription, parkLots);

        const char *testVehicleDescription = testVehcile.description();

        for (size_t counter = 0; counter < 13; ++counter)
        {
            REQUIRE(testVehicleDescription[counter] == vehicleDescription[counter]);
        }  
    }

    SECTION("testing constructor park lots")
    {
        char licensePlate[10] = "X 0853 KP";
        char vehicleDescription[14] = "BMW E91 330xd";
        size_t parkLots = 1;

        Vehicle testVehcile(licensePlate, vehicleDescription, parkLots);

        REQUIRE(testVehcile.space() == parkLots);
    }
}