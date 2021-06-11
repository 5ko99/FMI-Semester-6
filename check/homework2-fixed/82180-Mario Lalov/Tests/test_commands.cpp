#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Person/person.h"
#include "../Vehicle/vehicle.h"
#include "../Commands/file_commands.h"
#include "../DataContainer/data_container.h"

TEST_CASE("command initiation")
{

    SECTION("creating new person")
    {
        DataContainer data;

        FileCommands::initiateCommand("PERSON pesho 6", data);
        FileCommands::initiateCommand("PERSON gosho 1", data);

        REQUIRE(data.peopleList[0]->getName() == "pesho");
        REQUIRE(data.peopleList[1]->getName() == "gosho");
    }

    SECTION("creating new vehicle")
    {
        DataContainer data;

        FileCommands::initiateCommand("VEHICLE CA1234XX  desc", data);
        FileCommands::initiateCommand("VEHICLE AA1234XX smth", data);

        REQUIRE(data.vehiclesList[0]->getRegistration() == "CA1234XX");
        REQUIRE(data.vehiclesList[1]->getRegistration() == "AA1234XX");
    }

    SECTION("reading strings in quotations")
    {
        DataContainer data;

        FileCommands::initiateCommand("VEHICLE CA1234XX  \"desc smth\"", data);
        FileCommands::initiateCommand("PERSON \"pesho ivanov\" 5", data);

        REQUIRE(data.vehiclesList[0]->getDescription() == "desc smth");
        REQUIRE(data.peopleList[0]->getName() == "pesho ivanov");
    }

    SECTION("acquiring and releasing")
    {
        DataContainer data;

        FileCommands::initiateCommand("PERSON pesho 2", data);
        FileCommands::initiateCommand("PERSON gosho 3", data);

        FileCommands::initiateCommand("VEHICLE CA1234XX  desc", data);
        FileCommands::initiateCommand("VEHICLE AA1234XX smth", data);

        FileCommands::initiateCommand("ACQUIRE 2 AA1234XX", data);
        FileCommands::initiateCommand("ACQUIRE 2 CA1234XX", data);

        SECTION("default acquire")
        {
            REQUIRE(data.vehiclesList[0]->getOwner()->getId() == data.peopleList[0]->getId());
            REQUIRE(data.vehiclesList[1]->getOwner()->getId() == data.peopleList[0]->getId());
        }

        FileCommands::initiateCommand("Release 2 AA1234XX", data);

        SECTION("release")
        {
            REQUIRE(data.vehiclesList[1]->getOwner() == nullptr);
        }

        FileCommands::initiateCommand("acquire 2 CA1234XX", data);

        SECTION("acquire already owned vehicle")
        {
            REQUIRE(data.vehiclesList[0]->getOwner()->getId() == data.peopleList[0]->getId());
        }
    }

    SECTION("remove")
    {
        DataContainer data;

        SECTION("remove person")
        {
            FileCommands::initiateCommand("PERSON pesho 2", data);
            FileCommands::initiateCommand("PERSON gosho 3", data);

            FileCommands::initiateCommand("REMOVE 2", data);

            REQUIRE_THROWS_AS(getPersonIndex(2, data.peopleList), std::invalid_argument);
        }
    }
}

TEST_CASE("helpers")
{
    SECTION("to upper")
    {
        std::string input = "aBcd";
        toUpper(input);

        REQUIRE(input == "ABCD");
    }

    SECTION("is number")
    {
        std::string input = "46183259";

        REQUIRE(isNumber(input));
    }

    SECTION("get type")
    {
        REQUIRE(getType("CA1234XX") == VEHICLE);
        REQUIRE(getType("12345") == PERSON);
        REQUIRE(getType("VEHICLES") == VEHICLES_COM);
        REQUIRE(getType("PEOPLE") == PEOPLE_COM);
    }
}
