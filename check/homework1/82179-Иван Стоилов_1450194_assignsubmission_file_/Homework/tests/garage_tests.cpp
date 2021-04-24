#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "..\Garage\garage.hpp"
#include "..\Vehicle\vehicle.hpp"

TEST_CASE("garage")
{
    SECTION("Testing garage constructor")
    {
        size_t garageCapacity = 10;
        Garage testGarage(garageCapacity);

        REQUIRE(testGarage.empty() == true);
        REQUIRE(testGarage.size() == 0);
    }

    SECTION("testing assigment operator")
    {
        size_t originalGarageCapacity = 10;
        Garage originalTestGarage(originalGarageCapacity);

        size_t sourceGarageCapacity = 5;
        Garage sourceTestGarage(sourceGarageCapacity);

        originalTestGarage = sourceTestGarage;

        REQUIRE(originalTestGarage.empty() == true);
        REQUIRE(originalTestGarage.size() == 0);
    }

    SECTION("testing insert function")
    {
        size_t garageCapacity = 10;

        Garage testGarage(garageCapacity);

        char licensePlate[10] = "X 0853 KP";
        char vehicleDescription[14] = "BMW E91 330xd";
        size_t parkLots = 1;

        Vehicle testVehcile(licensePlate, vehicleDescription, parkLots);

        testGarage.insert(testVehcile);

        REQUIRE(testGarage.empty() == false);
        REQUIRE(testGarage.size() == 1);
    }

    SECTION("testing insert function with same cars")
    {
        size_t garageCapacity = 10;

        Garage testGarage(garageCapacity);

        char licensePlate[10] = "X 0853 KP";
        char vehicleDescription[14] = "BMW E91 330xd";
        size_t parkLots = 1;

        char doplicateLicensePlate[10] = "X 0853 KP";
        char doblicateVehicleDescription[14] = "BMW E91 330xd";
        size_t doblicateParkLots = 1;

        Vehicle testVehcile(licensePlate, vehicleDescription, parkLots);
        Vehicle doblicateTestVehcile(doplicateLicensePlate, doblicateVehicleDescription, doblicateParkLots);

        testGarage.insert(testVehcile);
        testGarage.insert(doblicateTestVehcile);

        REQUIRE(testGarage.empty() == false);
        REQUIRE(testGarage.size() == 1);
    }

    SECTION("testing insert function with same cars")
    {
        size_t garageCapacity = 10;

        Garage testGarage(garageCapacity);

        char licensePlate[10] = "X 0853 KP";
        char vehicleDescription[14] = "BMW E91 330xd";
            size_t parkLots = 1;

        char doplicateLicensePlate[10] = "X 0853 KM";
        char doblicateVehicleDescription[14] = "BMW E91 330xd";
        size_t doblicateParkLots = 1;

        Vehicle testVehcile(licensePlate, vehicleDescription, parkLots);
        Vehicle doblicateTestVehcile(doplicateLicensePlate, doblicateVehicleDescription, doblicateParkLots);

        testGarage.insert(testVehcile);
        testGarage.insert(doblicateTestVehcile);

        testGarage.erase(doblicateTestVehcile.registration());

        REQUIRE(testGarage.empty() == false);
        REQUIRE(testGarage.size() == 1);
    }
}