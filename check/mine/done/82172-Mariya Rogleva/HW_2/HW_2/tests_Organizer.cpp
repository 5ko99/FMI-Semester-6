#include "catch2.hpp"
#include "Person.hpp"
#include "Organizer.hpp"

TEST_CASE( "Organizer tests", "[Organizer]" )
{
    Organizer& org = Organizer::getInstance();

    SECTION("adding people")
    {
        org.addPerson("Ivan", 45);
        org.addPerson("Test Petrov", 12);
        org.addPerson("Dragan", 55);
        org.addPerson("Maria", 20);
        REQUIRE(org.getPersonId(0) == 45);
        REQUIRE(org.getPersonId(1) == 12);
        REQUIRE(org.getPersonId(2) == 55);
        REQUIRE(org.getPersonId(3) == 20);
    }
    // SECTION("adding person with unavailable id")
    // {
    //     try
    //     {
    //         org.addPerson("Maria", 20);
    //     }
    //     catch(const std::exception& e)
    //     {
    //         REQUIRE(e.what() == "A person with that ID already exists.");
    //     }
    // }
    SECTION("adding vehicles")
    {
        org.addVehicle("AB1234CD", "Toyota");
        org.addVehicle("XY1234AB", "Subaru");
        org.addVehicle("CA1234MP", "Toyota");
        org.addVehicle("B2222BB", "Subaru");
        REQUIRE(org.getVehicleReg(0) == "AB1234CD");
        REQUIRE(org.getVehicleReg(1) == "XY1234AB");
        REQUIRE(org.getVehicleReg(2) == "CA1234MP");
        REQUIRE(org.getVehicleReg(3) == "B2222BB");
    }
    SECTION("acquire") 
    {
        org.acquire(12, "XY1234AB");

        REQUIRE(org.getPerson(12)->numberOfVehicles() == 1);
        REQUIRE(org.getPerson(12)->getVehicle(0)->getReg() == "XY1234AB");
        REQUIRE(org.getVehicle("XY1234AB").getOwnerId() == 12);

        org.acquire(12, "AB1234CD");

        REQUIRE(org.getPerson(12)->numberOfVehicles() == 2);
        REQUIRE(org.getPerson(12)->getVehicle(1)->getReg() == "AB1234CD");
        REQUIRE(org.getVehicle("AB1234CD").getOwnerId() == 12);

        org.acquire(45, "XY1234AB");
        REQUIRE(org.getPerson(45)->numberOfVehicles() == 1);
        REQUIRE(org.getPerson(12)->numberOfVehicles() == 1);
        REQUIRE(org.getVehicle("XY1234AB").getOwnerId() == 45);
        REQUIRE(org.getPerson(12)->getVehicle(0)->getReg() == "AB1234CD");
    }
    SECTION("release")
    {
        org.release(45, "XY1234AB");
        REQUIRE(org.getPerson(45)->numberOfVehicles() == 0);
        REQUIRE(org.getVehicle("XY1234AB").getOwnerId() == 0);
    }
    SECTION("remove person")
    {
        org.remove(12);
        REQUIRE_THROWS_AS(org.getPerson(12), std::runtime_error);
        REQUIRE(org.getVehicle("AB1234CD").getOwnerId() == 0);
    }
    SECTION("remove vehicle")
    {
        org.remove("CA1234MP");
        REQUIRE_THROWS_AS(org.getVehicle("CA1234MP"), std::runtime_error);
        REQUIRE(org.getPerson(45)->numberOfVehicles() == 0);
    }
}
