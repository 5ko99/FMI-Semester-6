#include "Person.h"

Person::Person(std::string name, size_t id) {
    this->name = name;
    this->id = id;
    this->vehicles = {};
}

size_t Person::getId() {
    return id;
}

void Person::removeVehicle(Vehicle* vehicle) {
    size_t pos = 0;
    bool erase = false;
    for (size_t i = 0; i < vehicles.size(); i++) {
        if (vehicles[i]->getRegistrationNumber() == vehicle->getRegistrationNumber()) {
            erase = true;
            pos = i;
            break;
        }
    }

    if (erase) {
        vehicles.erase(std::next(vehicles.begin(), pos));
        vehicle->setOwner(nullptr);
    }
}

void Person::addVehicle(Vehicle* vehicle) {
    vehicles.push_back(vehicle);
    vehicle->setOwner(this);
}

Person::~Person() {
    for (Vehicle* vehicle : vehicles) {
        removeVehicle(vehicle);
    }
}

std::string Person::getName() {
    return name;
}

size_t Person::getVehiclesCount() {
    return vehicles.size();
}

void Person::show() {
    printElement("ID", 5);
    printElement("NAME", 20);
    printElement("VEHICLES", 10);
    printElement('\n', 0);

    printElement(id, 5);
    printElement(name, 20);

    if (vehicles.size()) {
        printElement(vehicles[0]->getRegistrationNumber(), 10);
        printElement('\n', 0);

        for (size_t i = 1; i < vehicles.size(); i++) {
            printElement(vehicles[i]->getRegistrationNumber(), 35);
            printElement('\n', 0);
        }
    }
}
