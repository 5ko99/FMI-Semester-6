#include "catch2.hpp"
#include "../include/Database.h"

TEST_CASE("Testing the database add person function")
{
    DataBase db;
    db.addPerson("Ivan", 10);
    REQUIRE(db.getPerson(10) != nullptr);
}
TEST_CASE("Testing the database add vehicle function")
{
    DataBase db;
    Registration reg("AH4545TH");
    db.addVehicle(reg, "Dark opel");
    REQUIRE(db.getVehicle(reg) != nullptr);
}
TEST_CASE("Testing the database assign and release vehicle to person function")
{
    DataBase db;
    Registration reg("AH4545TH");
    db.addVehicle(reg, "Dark opel");
    db.addPerson("Ivan", 10);
    db.assignVehicleToPerson(10, reg);
    REQUIRE(db.getPerson(10)->cntOfVehicles() == 1);
    db.releaseVehicleFromPerson(10, reg);
    REQUIRE(db.getPerson(10)->cntOfVehicles() == 0);
}
TEST_CASE("Testing the database remove person function")
{
    DataBase db;
    db.addPerson("Ivan", 10);
    db.removePerson(10);
    REQUIRE(db.getPerson(10) == nullptr);
}
TEST_CASE("Testing the database remove vehicle function")
{
    DataBase db;
    Registration reg("AH4545TH");
    db.addVehicle(reg, "Dark opel");
    db.removeVehicle(reg);
    REQUIRE(db.getVehicle(reg) == nullptr);
}
