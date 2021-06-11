#define CATCH_CONFIG_MAIN

#include "../Catch2/catch2.h"
#include "../Headers/CommandParser.h"

TEST_CASE("Registration tests") {
    Registration registration("CB1234AB");
    REQUIRE(registration.getRegistration() == "CB1234AB");

    SECTION("Copy constructor") {
        Registration registrationCopy(registration);

        REQUIRE(registration.getRegistration() == registrationCopy.getRegistration());
    }

    SECTION("Operator=") {
        Registration registrationCopy = registration;

        REQUIRE(registration.getRegistration() == registrationCopy.getRegistration());
    }
}

TEST_CASE("Vehicle tests and Person tests") {
    Person person("Ivan Ivanov", 1);

    REQUIRE(person.getName() == "Ivan Ivanov");
    REQUIRE(person.getId() == 1);
    REQUIRE(person.getVehicles().empty() == true);

    Registration registration("C1234AB");
    Vehicle vehicle(registration, "this is description");

    REQUIRE(vehicle.getRegistration() == "C1234AB");
    REQUIRE(vehicle.getDescription() == "this is description");

    vehicle.setOwner(person);

    SECTION("Copy constructor") {
        Vehicle vehicleCopy(vehicle);

        REQUIRE (vehicle.getRegistration() == vehicleCopy.getRegistration());
        REQUIRE (vehicle.getDescription() == vehicleCopy.getDescription());
        REQUIRE (vehicle.getOwner() == vehicleCopy.getOwner());
    }

    SECTION("Operator=") {
        Vehicle vehicleCopy = vehicle;

        REQUIRE (vehicle.getRegistration() == vehicleCopy.getRegistration());
        REQUIRE (vehicle.getDescription() == vehicleCopy.getDescription());
        REQUIRE (vehicle.getOwner() == vehicleCopy.getOwner());
    }

    REQUIRE(person.getVehicles().size() == 1);

    SECTION("Copy constructor") {
        Person personCopy(person);

        REQUIRE(person.getName() == personCopy.getName());
        REQUIRE(person.getId() == personCopy.getId());
        REQUIRE(person.getVehicles().size() == personCopy.getVehicles().size());
        REQUIRE(person.getVehicles().back() == personCopy.getVehicles().back());
    }

    SECTION("Operator=") {
        Person personCopy = person;

        REQUIRE(person.getName() == personCopy.getName());
        REQUIRE(person.getId() == personCopy.getId());
        REQUIRE(person.getVehicles().size() == personCopy.getVehicles().size());
        REQUIRE(person.getVehicles().back() == personCopy.getVehicles().back());
    }
}

TEST_CASE("CommandParser tests") {
    CommandParser commandParser;
    std::string command;

    SECTION("VEHICLE command tests") {
        command = "VeHiCle  CB1234AB  \"this is description  \"  ";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getVehicles().back()->getRegistration() == "CB1234AB");
        REQUIRE(commandParser.getVehicles().back()->getDescription() == "this is description  ");

        command = "VEHICLE C1234AB asd";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getVehicles().size() == 2);
        REQUIRE(commandParser.getVehicles().back()->getRegistration() == "C1234AB");
        REQUIRE(commandParser.getVehicles().back()->getDescription() == "asd");

        command = "person Vanko 1";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getPeople().size() == 1);
        REQUIRE(commandParser.getPeople().back()->getName() == "Vanko");
        REQUIRE(commandParser.getPeople().back()->getId() == 1);

        command = "PerSon \"Ivan Ivanov\" 10";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getPeople().size() == 2);
        REQUIRE(commandParser.getPeople().back()->getName() == "Ivan Ivanov");
        REQUIRE(commandParser.getPeople().back()->getId() == 10);

        command = "veHICLE  C1234AB \"different desc\"";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getVehicles().size() == 2);
        REQUIRE(commandParser.getVehicles().back()->getRegistration() == "C1234AB");
        REQUIRE(commandParser.getVehicles().back()->getDescription() == "asd");

        command = "VEHICLE CB234AB asd";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getVehicles().size() == 2);

        command = "VEHICLE C1234aB asd";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getVehicles().size() == 2);

        command = "VEHICLE C12348B asd";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getVehicles().size() == 2);

        command = "VEHICLE CA1234B asd";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getVehicles().size() == 2);

        command = "VEHICLE ABCDEFAB asd";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getVehicles().size() == 2);

        command = "VEHICLE 1234567 asd";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getVehicles().size() == 2);
    }

    SECTION("PERSON command tests") {
        command = "VeHiCle  CB1234AB  \"this is description  \"  ";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getVehicles().back()->getRegistration() == "CB1234AB");
        REQUIRE(commandParser.getVehicles().back()->getDescription() == "this is description  ");

        command = "VEHICLE C1234AB asd";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getVehicles().size() == 2);
        REQUIRE(commandParser.getVehicles().back()->getRegistration() == "C1234AB");
        REQUIRE(commandParser.getVehicles().back()->getDescription() == "asd");

        command = "person Vanko 1";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getPeople().size() == 1);
        REQUIRE(commandParser.getPeople().back()->getName() == "Vanko");
        REQUIRE(commandParser.getPeople().back()->getId() == 1);

        command = "PerSon \"Ivan Ivanov\" 10";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getPeople().size() == 2);
        REQUIRE(commandParser.getPeople().back()->getName() == "Ivan Ivanov");
        REQUIRE(commandParser.getPeople().back()->getId() == 10);

        command = "PerSon \"Petar Petrov\" 10";
        REQUIRE(commandParser.getPeople().size() == 2);
        REQUIRE(commandParser.getPeople().back()->getName() == "Ivan Ivanov");
        REQUIRE(commandParser.getPeople().back()->getId() == 10);
    }

    SECTION("ACQUIRE and RELEASE commands") {
        command = "VeHiCle  CB1234AB  \"this is description  \"  ";
        commandParser.parseCommand(command);
        command = "VEHICLE C1234AB asd";
        commandParser.parseCommand(command);

        command = "person Vanko 1";
        commandParser.parseCommand(command);
        command = "PerSon \"Ivan Ivanov\" 10";
        commandParser.parseCommand(command);

        command = "AcQuiRe 1 C1234AB";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getPeople()[0]->getVehicles()[0]->getRegistration() == "C1234AB");
        REQUIRE(commandParser.getVehicles()[1]->getOwner()->getId() == 1);

        command = "ACQUIRE 10 C1234AB";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getPeople()[0]->getVehicles().size() == 0);
        REQUIRE(commandParser.getPeople()[1]->getVehicles()[0]->getRegistration() == "C1234AB");
        REQUIRE(commandParser.getVehicles()[1]->getOwner()->getId() == 10);

        command = "Acquire 1 X1234AB";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getPeople()[0]->getVehicles().size() == 0);

        command = "acquire 10 CB1234AB";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getPeople()[1]->getVehicles().size() == 2);
        REQUIRE(commandParser.getPeople()[1]->getVehicles()[1]->getDescription() == "this is description  ");

        command = "aCqUiRe 3 C1234AB";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getVehicles()[1]->getOwner()->getId() == 10);

        command = "RelEase 1 C1234AB";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getVehicles()[1]->getOwner()->getId() == 10);

        command = "release 10 C1234AB";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getPeople()[1]->getVehicles().size() == 1);
        REQUIRE(commandParser.getVehicles()[1]->getOwner() == nullptr);

        command = "RELEASE 1 C1234AB";
        commandParser.parseCommand(command);
        REQUIRE(commandParser.getPeople()[1]->getVehicles().size() == 1);
        REQUIRE(commandParser.getVehicles()[1]->getOwner() == nullptr);
    }
}
