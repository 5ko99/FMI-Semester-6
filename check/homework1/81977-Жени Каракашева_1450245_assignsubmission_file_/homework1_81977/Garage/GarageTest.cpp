#define CATCH_CONFIG_MAIN
#include "../catch2/catch2.hpp"
#include "Garage.h"

//to compile: g++ GarageTest.cpp Garage.cpp ../Vehicle/Vehicle.cpp ../MyString/MyString.cpp ../catch2/catch2.cpp

TEST_CASE("at() function check")
{
    Garage test(10);

    Vehicle firstVehicle("H 2090","Renault",4);
    Vehicle secondVehicle("H 5432","BMW",2);
    Vehicle thirdVehicle("CA 2356","Mercedes",3);

    test.insert(firstVehicle);
    test.insert(secondVehicle);
    test.insert(thirdVehicle);

    REQUIRE(strcmp(test.at(0).registration(),"H 2090") == 0);
    REQUIRE(strcmp(test.at(0).description(),"Renault") == 0);

    REQUIRE(strcmp(test.at(1).registration(),"H 5432") == 0);
    REQUIRE(strcmp(test.at(1).description(),"BMW") == 0);

    REQUIRE(strcmp(test.at(2).registration(),"CA 2356") == 0);
    REQUIRE(strcmp(test.at(2).description(),"Mercedes") == 0);
}

TEST_CASE("Test for operator[]")
{
    Garage test(10);
    Vehicle firstVehicle("H 2090", "Renault", 2);
    Vehicle secondVehicle("H 5432", "BMW", 2);
    Vehicle thirdVehicle("CA 2356", "Mercedes", 2);
    test.insert(firstVehicle);
    test.insert(secondVehicle);
    test.insert(thirdVehicle);

    REQUIRE(strcmp(test[0].registration(), "H 2090") == 0);
    REQUIRE(strcmp(test[0].description(), "Renault") == 0);

    REQUIRE(strcmp(test[1].registration(), "H 5432") == 0);
    REQUIRE(strcmp(test[1].description(), "BMW") == 0);

    REQUIRE(strcmp(test[2].registration(), "CA 2356") == 0);
    REQUIRE(strcmp(test[2].description(), "Mercedes") == 0);
}

TEST_CASE("Clear() method test")
{
    Garage test(10);
    Vehicle firstVehicle("H 2090", "Renault", 2);
    Vehicle secondVehicle("H 5432", "BMW", 2);

    test.insert(firstVehicle);
    test.insert(secondVehicle);
    REQUIRE(test.size() == 2);
    REQUIRE(test.empty() == false);

    test.clear();
    REQUIRE(test.size() == 0);
    REQUIRE(test.empty() == true);
}

TEST_CASE("Erase() method test")
{
    Garage test(10);

    Vehicle firstVehicle("H 2090", "Renault", 2);
    Vehicle secondVehicle("H 5432", "BMW", 2);
    Vehicle thirdVehicle("CA 2356", "Mercedes", 2);

    test.insert(firstVehicle);
    test.insert(secondVehicle);
    test.insert(thirdVehicle);

    REQUIRE(test.size() == 3);
    test.erase("CA 2356");
    REQUIRE(test.size() == 2);
}

TEST_CASE("Find() method test")
{
    Garage test(6);

    Vehicle firstVehicle("H 2090", "Renault", 2);
    Vehicle secondVehicle("CA 2356", "BMW", 2);
    Vehicle thirdVehicle("CB 3456", "Mercedes", 2);

    test.insert(firstVehicle);
    test.insert(secondVehicle);
    test.insert(thirdVehicle);

    MyString testReg("H 2090");
    MyString testRegTwo("CA 2356");

    const Vehicle *foundOne = test.find(testReg.c_str());
    REQUIRE(strcmp(foundOne->registration(),testReg.c_str()) == 0);

    const Vehicle *foundTwo = test.find(testRegTwo.c_str());
    REQUIRE(strcmp(foundTwo->registration(),testRegTwo.c_str()) == 0);

    const Vehicle *foundThree = test.find("CB 3456");
    REQUIRE(foundThree == nullptr);
}