#include "catch2.hpp"
#include "MyString.h"
#include "Garage.h"

TEST_CASE("Insert, Erase and Size Testing")
{
    Garage garage1(15);
    Garage garage2(garage1);

    Vehicle vehicle1("Test", "Medium", 6);
    Vehicle vehicle2("Car", "Small", 4);
    Vehicle vehicle3("Bus", "Big", 8);
    Vehicle vehicle4("Bus", "Small", 6);
    Vehicle vehicle5("Scooter", " VerySmall", 1);
    Vehicle vehicle6("Motorcycle", "Small", 2);

    garage1.insert(vehicle1);
    garage2.insert(vehicle1);

    garage1.insert(vehicle1); //Error message is deliberate
    garage2.insert(vehicle1); //Error message is deliberate

    garage1.insert(vehicle2);
    garage2.insert(vehicle3);

    garage1.insert(vehicle3); //Error message is deliberate
    garage2.insert(vehicle4); //Error message is deliberate

    garage1.insert(vehicle5);
    garage2.insert(vehicle6); //Error message is deliberate

    REQUIRE(garage1.size() == 3);
    REQUIRE(garage2.size() == 2);

    garage1.erase("Test");
    garage1.erase("Scooter");

    garage2.erase("Scooter");
    garage2.erase("Test");

    REQUIRE(garage1.size() == 1);
    REQUIRE(garage2.size() == 1);
}

TEST_CASE("At and Operator[] Testing for Garage")
{
    Garage garage1(15);
    Garage garage2(garage1);

    Vehicle vehicle1("Test", "Medium", 6);
    Vehicle vehicle2("Car", "Small", 4);
    Vehicle vehicle3("Bus", "Big", 8);
    Vehicle vehicle4("Bus", "Small", 6);
    Vehicle vehicle5("Scooter", " VerySmall", 1);
    Vehicle vehicle6("Motorcycle", "Small", 2);

    garage1.insert(vehicle1);
    garage2.insert(vehicle1);

    garage1.insert(vehicle2);
    garage2.insert(vehicle3);

    garage1.insert(vehicle5);

    REQUIRE(garage1.at(1).get_description() == vehicle2.get_description());
    REQUIRE(garage1.at(0).get_description() == vehicle1.get_description());

    REQUIRE(garage2.at(0).get_registration() == vehicle1.get_registration());
    REQUIRE(garage1.at(2).get_registration() == vehicle5.get_registration());

    REQUIRE(garage1.at(2).get_space() == vehicle5.get_space());
    REQUIRE(garage2.at(1).get_space() == vehicle3.get_space());

    REQUIRE(garage1[1].get_registration() == vehicle2.get_registration());
    REQUIRE(garage1[0].get_registration() == vehicle1.get_registration());

    REQUIRE(garage2[0].get_space() == vehicle1.get_space());
    REQUIRE(garage1[2].get_space() == vehicle5.get_space());

    REQUIRE(garage1[2].get_description() == vehicle5.get_description());
    REQUIRE(garage2[1].get_description() == vehicle3.get_description());
}

TEST_CASE("Empty and Clear Testing for Garage")
{
    Garage garage1(15);
    Garage garage2(garage1);

    Vehicle vehicle1("Test", "Medium", 6);
    Vehicle vehicle2("Car", "Small", 4);
    Vehicle vehicle3("Bus", "Big", 8);
    Vehicle vehicle4("Bus", "Small", 6);
    Vehicle vehicle5("Scooter", " VerySmall", 1);
    Vehicle vehicle6("Motorcycle", "Small", 2);

    garage1.insert(vehicle1);
    garage2.insert(vehicle1);

    garage1.insert(vehicle2);
    garage2.insert(vehicle3);

    garage1.insert(vehicle5);

    REQUIRE(garage1.empty() == 0);
    REQUIRE(garage2.empty() == 0);

    garage1.clear();
    garage2.clear();

    REQUIRE(garage1.empty() == 1);
    REQUIRE(garage2.empty() == 1);

    garage1.insert(vehicle6);
    garage2.insert(vehicle3);

    REQUIRE(garage1.empty() == 0);
    REQUIRE(garage2.empty() == 0);
}

TEST_CASE("Find Testing for Garage")
{
    Garage garage1(15);
    Garage garage2(garage1);

    Vehicle vehicle1("Test", "Medium", 6);
    Vehicle vehicle2("Car", "Small", 4);
    Vehicle vehicle3("Bus", "Big", 8);
    Vehicle vehicle4("Bus", "Small", 6);
    Vehicle vehicle5("Scooter", " VerySmall", 1);
    Vehicle vehicle6("Motorcycle", "Small", 2);

    garage1.insert(vehicle1);
    garage2.insert(vehicle1);

    garage1.insert(vehicle2);
    garage2.insert(vehicle3);

    garage1.insert(vehicle5);

    Vehicle *vehiclePointer1 = garage1.find("Scooter");
    Vehicle *vehiclePointer2 = garage1.find("Test");
    Vehicle *vehiclePointer3 = garage2.find("Test");
    Vehicle *vehiclePointer4 = garage2.find("Bus");
    Vehicle *vehiclePointer5 = garage2.find("Plane"); // no vehicle named Plane

    REQUIRE(vehiclePointer1->get_description() == vehicle5.get_description());
    REQUIRE(vehiclePointer2->get_description() == vehicle1.get_description());

    REQUIRE(vehiclePointer2->get_registration() == vehicle1.get_registration());
    REQUIRE(vehiclePointer3->get_registration() == vehicle1.get_registration());

    REQUIRE(vehiclePointer3->get_space() == vehicle1.get_space());
    REQUIRE(vehiclePointer4->get_space() == vehicle3.get_space());

    REQUIRE(vehiclePointer5 == nullptr);
}

TEST_CASE("Operator= Testing for Garage")
{
    Garage garage1(20);

    Vehicle vehicle1("Test", "Medium", 6);
    Vehicle vehicle2("Car", "Small", 4);
    Vehicle vehicle3("Bus", "Big", 8);
    Vehicle vehicle4("Bus", "Small", 6);
    Vehicle vehicle5("Scooter", " VerySmall", 1);
    Vehicle vehicle6("Motorcycle", "Small", 2);

    garage1.insert(vehicle1);
    garage1.insert(vehicle2);
    garage1.insert(vehicle3);
    garage1.insert(vehicle6);

    Garage garage2(garage1);

    garage2.insert(vehicle4); //Error message is deliberate
    garage2.insert(vehicle5); //Error message is deliberate

    const char *string1 = garage2[1].get_description();
    const char *string2 = garage2[0].get_description();

    const char *string3 = garage2[2].get_registration();
    const char *string4 = garage2[3].get_registration();

    size_t space1 = garage2[3].get_space();
    size_t space2 = garage2[0].get_space();

    REQUIRE(garage1[1].get_description() == string1);
    REQUIRE(garage1[0].get_description() == string2);

    REQUIRE(garage1[2].get_registration() == string3);
    REQUIRE(garage1[3].get_registration() == string4);

    REQUIRE(garage1[3].get_space() == space1);
    REQUIRE(garage1[0].get_space() == space2);

    Garage garage3(5);

    garage3 = garage1;

    
    REQUIRE(garage3[1].get_description() == string1);
    REQUIRE(garage3[0].get_description() == string2);

    REQUIRE(garage3[2].get_registration() == string3);
    REQUIRE(garage3[3].get_registration() == string4);

    REQUIRE(garage3[3].get_space() == space1);
    REQUIRE(garage3[0].get_space() == space2);

    garage3.erase(string3);
    garage3.erase(string4);

    garage2 = garage3;

    REQUIRE_FALSE(garage2[2].get_registration() == string3);
    REQUIRE_FALSE(garage2[3].get_registration() == string4);

    Garage garage4(0); //Deliberate throw not a real error!

}