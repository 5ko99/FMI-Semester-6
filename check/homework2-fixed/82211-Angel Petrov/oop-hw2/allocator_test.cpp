#define CATCH_CONFIG_MAIN
#include <vector>
#include "catch2.hpp"
#include "allocator.h"

TEST_CASE ("constructor, getInstance, addPerson/Vehicle, removePerson/Vehicle, acquire, release") {

    Allocator* alloc = Allocator::getInstance();
    Registration reg("A1234BC");

    alloc->addPerson("Name", 1);
    alloc->addVehicle(reg, "A vehicle.");
    alloc->acquire(1, reg);

    std::vector<Person> people = alloc->getPeople();
    std::vector<Vehicle> vehicles = alloc->getVehicles();
    std::vector<Vehicle*> personVehicles = people[0].getVehicles();

    CHECK(people[0].getID() == 1);
    CHECK(vehicles[0].getLicensePlate() == reg);
    CHECK(vehicles[0].getOwner()->getID() == people[0].getID());
    CHECK(personVehicles[0]->getLicensePlate() == reg);

    alloc->release(1, reg);
    alloc->removePerson(1);
    alloc->removeVehicle(reg);

    CHECK(!alloc->getPeopleSize());
    CHECK(!alloc->getVehiclesSize());
}
