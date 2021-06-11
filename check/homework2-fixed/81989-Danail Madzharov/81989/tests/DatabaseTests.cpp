#include "catch_amalgamated.hpp"
#include "../Database.h"

TEST_CASE("Should add a person to the database") {
    Database database;
    Person* person = new Person("Ivan", 12);
    int currentSizeOfIds = database.getpeopleIds().size();
    int currentSizeOfPeople = database.getPeople().size();
    database.addPerson(person);
    REQUIRE(database.getpeopleIds().size() == currentSizeOfIds + 1);
    REQUIRE(database.getPeople().size() == currentSizeOfPeople + 1);
    REQUIRE(database.getPersonById(12) == person);
}

TEST_CASE("Should add a vehicle to the database") {
    Database database;
    Registration* reg = new Registration("AA3333BB");
    Vehicle* vehicle = new Vehicle(reg, "A simple vehicle");
    int currentSizeOfRegs = database.getVehiclesRegistrations().size();
    int currentSizeOfCars = database.getCars().size();
    database.addVehicle(vehicle);
    REQUIRE(database.getVehiclesRegistrations().size() == currentSizeOfRegs + 1);
    REQUIRE(database.getCars().size() == currentSizeOfCars + 1);
    REQUIRE(database.getVehicleByRegNumber("AA3333BB") == vehicle);
}

TEST_CASE("Should make a person an owner of vehicle") {
    Database database;
    Person* person = new Person("Ivan", 12);
    Registration* reg = new Registration("AA3333BB");
    Vehicle* vehicle = new Vehicle(reg, "A simple vehicle");
    database.addVehicle(vehicle);
    database.addPerson(person);
    database.setCarOwner(person, vehicle);
    REQUIRE(database.getVehicleByRegNumber("AA3333BB")->getOwner() == person);
    REQUIRE(database.getPersonById(12)->getOwnedCars().front() == reg);
}

TEST_CASE("Should release a person of vehicle") {
    Database database;
    Person* person = new Person("Ivan", 12);
    Registration* reg = new Registration("AA3333BB");
    Vehicle* vehicle = new Vehicle(reg, "A simple vehicle");
    database.addVehicle(vehicle);
    database.addPerson(person);
    database.setCarOwner(person, vehicle);
    database.removeCarOwner(person, vehicle);
    REQUIRE(database.getVehicleByRegNumber("AA3333BB")->getOwner() == nullptr);
    REQUIRE(database.getPersonById(12)->getOwnedCars().empty());
}

TEST_CASE("Should change owner") {
    Database database;
    Person* person = new Person("Ivan", 12);
    Person* person2 = new Person("Petar", 15);
    Registration* reg = new Registration("AA3333BB");
    Vehicle* vehicle = new Vehicle(reg, "A simple vehicle");
    database.addVehicle(vehicle);
    database.addPerson(person2);
    database.addPerson(person);
    database.setCarOwner(person, vehicle);
    database.setCarOwner(person2, vehicle);
    REQUIRE(database.getVehicleByRegNumber("AA3333BB")->getOwner() == person2);
    REQUIRE(database.getPersonById(12)->getOwnedCars().empty());
    REQUIRE(database.getPersonById(15)->getOwnedCars().front() == reg);
}


TEST_CASE("Should delete car from database") {
    Database database;
    Registration* reg = new Registration("AA3333BB");
    Vehicle* vehicle = new Vehicle(reg, "A simple vehicle");
    int currentSizeOfRegs = database.getVehiclesRegistrations().size();
    int currentSizeOfCars = database.getCars().size();
    database.addVehicle(vehicle);
    database.deleteCarFromDatabase("AA3333BB");
    REQUIRE(database.getVehiclesRegistrations().size() == currentSizeOfRegs);
    REQUIRE(database.getCars().size() == currentSizeOfCars);
    REQUIRE(database.getVehicleByRegNumber("AA3333BB") == nullptr);
}

TEST_CASE("Should delete person from database") {
    Database database;
    Person* person = new Person("Ivan", 12);
    int currentSizeOfIds = database.getpeopleIds().size();
    int currentSizeOfPeople = database.getPeople().size();
    database.addPerson(person);
    database.deletePersonFromDatabase(12);
    REQUIRE(database.getpeopleIds().size() == currentSizeOfIds);
    REQUIRE(database.getPeople().size() == currentSizeOfPeople);
    REQUIRE(database.getPersonById(12) == nullptr);
}

TEST_CASE("Validate car reg with regex") {
    Database database;
    REQUIRE(database.validateRegNumber("A3333BB"));
    REQUIRE(database.validateRegNumber("AA3333BB"));
    REQUIRE_FALSE(database.validateRegNumber("aA3333BB"));
    REQUIRE_FALSE(database.validateRegNumber("AA3333B"));
    REQUIRE_FALSE(database.validateRegNumber("Random string"));
    REQUIRE_FALSE(database.validateRegNumber("AA333BB"));
    REQUIRE_FALSE(database.validateRegNumber("AAA333BB"));
}


TEST_CASE("Should find person by ID") {
    Database database;
    Person* person = new Person("Ivan", 12);
    REQUIRE(database.getPersonById(12) == nullptr);
    database.addPerson(person);
    REQUIRE(database.getPersonById(12) == person);
}

TEST_CASE("Should find car by reg") {
    Database database;
    Registration* reg = new Registration("AA3333BB");
    Vehicle* vehicle = new Vehicle(reg, "A simple vehicle");
    REQUIRE(database.getVehicleByRegNumber("AA3333BB") == nullptr);
    database.addVehicle(vehicle);
    REQUIRE(database.getVehicleByRegNumber("AA3333BB") == vehicle);
}
