
#include "../../Homework-2/Tests/Catch2/catch.hpp"

#include "../Headers/VehicleCollection.h"
#include "../Headers/PersonCollection.h"

TEST_CASE("void addVehicle(const Vehicle &vehicle) adds new vehicle") {

    // Arrange
    Vehicle v1(Registration("X1234BA"), "Audi");
    Vehicle v2(Registration("CA4444BA"), "Mitsubishi");
    Vehicle v3(Registration("X3333BA"), "Nissan");
    Vehicle v4(Registration("CB6565BA"), "Porsche");
    VehicleCollection vehicleCollection;

    // Act
    vehicleCollection.addVehicle(v1);
    vehicleCollection.addVehicle(v3);
    vehicleCollection.addVehicle(v2);

    // Assert
    REQUIRE(vehicleCollection[0].getRegistration() == v1.getRegistration());
    REQUIRE(vehicleCollection[1].getRegistration() == v3.getRegistration());
    REQUIRE(vehicleCollection[2].getRegistration() == v2.getRegistration());
}

TEST_CASE("void removeVehicle(const Registration &vehicleId, PersonCollection &personCollection) \n"
          "removes vehicle without destroying the Person object to which it may be connected") {

    // Arrange
    Vehicle v1(Registration("X1234BA"), "Audi");
    VehicleCollection vehicleCollection;
    vehicleCollection.addVehicle(v1);

    Person p1("Georgi Georgiev", 21);
    PersonCollection personCollection;
    personCollection.addPerson(p1);

    personCollection.acquireVehicle(21,
                                    Registration("X1234BA"),
                                    vehicleCollection);
    // Act
    vehicleCollection.removeVehicle(Registration("X1234BA"), personCollection);

    // Assert
    REQUIRE(vehicleCollection.findVehicle(Registration("X1234BA")) == nullptr);
    REQUIRE(personCollection[0].getVehiclesCount() == 0);
}
