#define CATCH_CONFIG_MAIN

#include "../../Homework-2/Tests/Catch2/catch.hpp"

#include "../Headers/VehicleCollection.h"
#include "../Headers/PersonCollection.h"

TEST_CASE("void addPerson(const Person &person) adds new person") {

    // Arrange
    Person p1("Georgi Georgiev", 21);
    Person p2("Ivan Ivanov", 31);
    Person p3("Ani Antonova", 20);
    PersonCollection personCollection;

    // Act
    personCollection.addPerson(p1);
    personCollection.addPerson(p2);
    personCollection.addPerson(p3);

    // Assert
    REQUIRE(personCollection[0].getId() == p1.getId());
    REQUIRE(personCollection[1].getId() == p2.getId());
    REQUIRE(personCollection[2].getId() == p2.getId());
}

// Arrange-Act-Assert, but such a long arrange here :)
TEST_CASE("void acquireVehicle(unsigned int ownerId, const Registration &vehicleId, "
          "VehicleCollection &vehicleCollection) "
          "set vehicle's owner to the this person "
          "and the vehicle is now part of it's owner collection") {

    // Arrange
    Vehicle v1(Registration("X1234BA"), "Opel");
    Vehicle v2(Registration("X4444BA"), "Subaru");
    Vehicle v3(Registration("X3333BA"), "Honda");
    Vehicle v4(Registration("X6565BA"), "Audi");

    VehicleCollection vehicleCollection;
    vehicleCollection.addVehicle(v1);
    vehicleCollection.addVehicle(v2);
    vehicleCollection.addVehicle(v3);
    vehicleCollection.addVehicle(v4);

    Person p1("Georgi Georgiev", 21);
    Person p2("Ivan Ivanov", 31);
    Person p3("Ani Antonova", 20);

    PersonCollection personCollection;
    personCollection.addPerson(p1);
    personCollection.addPerson(p2);
    personCollection.addPerson(p3);

    // Act
    personCollection.acquireVehicle(21, v1.getRegistration(), vehicleCollection);
    personCollection.acquireVehicle(21, v3.getRegistration(), vehicleCollection);

    // Assert
    REQUIRE(personCollection[0].getVehicle(0)->getRegistration() == v1.getRegistration());
    REQUIRE(personCollection[0].getVehicle(1)->getRegistration() == v3.getRegistration());
}

TEST_CASE("void releaseVehicle(unsigned int ownerId, const Registration &vehicleId) "
          "releases vehicle and then the person no longer owns that vehicle") {

    // Arrange
    Vehicle v1(Registration("X1234BA"), "Opel");
    Vehicle v2(Registration("X4444BA"), "Subaru");
    Vehicle v3(Registration("X3333BA"), "Honda");
    VehicleCollection vehicleCollection;
    vehicleCollection.addVehicle(v1);
    vehicleCollection.addVehicle(v2);
    vehicleCollection.addVehicle(v3);

    Person p1("Georgi Georgiev", 21);
    PersonCollection personCollection;
    personCollection.addPerson(p1);

    personCollection.acquireVehicle(21,
                                    Registration("X1234BA"),
                                    vehicleCollection);
    // Act
    personCollection.releaseVehicle(21, Registration("X1234BA"));

    // Assert
    REQUIRE(personCollection[0].getVehiclesCount() == 0);
    REQUIRE(vehicleCollection[0].getOwner() == nullptr);
}

TEST_CASE("void removePerson(unsigned int id) "
          "releases all vehicles that this person owns "
          "and then removes this person") {

    // Arrange
    Vehicle v1(Registration("X1234BA"), "Opel");
    Vehicle v2(Registration("X4444BA"), "Subaru");
    Vehicle v3(Registration("X3333BA"), "Honda");
    VehicleCollection vehicleCollection;
    vehicleCollection.addVehicle(v1);
    vehicleCollection.addVehicle(v2);
    vehicleCollection.addVehicle(v3);

    Person p1("Georgi Georgiev", 21);
    PersonCollection personCollection;
    personCollection.addPerson(p1);

    personCollection.acquireVehicle(21,
                                    Registration("X1234BA"),
                                    vehicleCollection);

    personCollection.acquireVehicle(21,
                                    Registration("X4444BA"),
                                    vehicleCollection);
    // Act
    personCollection.removePerson(21);

    // Assert
    REQUIRE(vehicleCollection[0].getOwner() == nullptr);
    REQUIRE(vehicleCollection[1].getOwner() == nullptr);
    REQUIRE(personCollection.peopleCount() == 0);
    REQUIRE(personCollection.findPerson(21) == nullptr);
}

