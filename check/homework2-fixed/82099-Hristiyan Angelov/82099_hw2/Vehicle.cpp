#include "Vehicle.h"

Vehicle::Vehicle(RegistrationNumber regNumber, std::string description, Person* owner) {
    this->regNumber = regNumber;
    this->description = description;

    if (owner) {
        this->owner = owner;
    }
    else {
        this->owner = nullptr;
    }
}

std::string Vehicle::getDescription() {
    return description;
}

RegistrationNumber Vehicle::getRegistrationNumber() {
    return regNumber;
}

bool Vehicle::hasOwner() {
    return owner == nullptr ? false : true;
}

void Vehicle::setOwner(Person* newOwner) {
    owner = newOwner;
}

Result<Person*> Vehicle::getOwner() {
    if (owner != nullptr) {
        return Result<Person*> { true, owner };
    }

    return Result<Person*> { false };
}

Vehicle::~Vehicle() {
    if (owner) {
        owner->removeVehicle(this);
    }
}

void Vehicle::show() {
    printElement("ID", 10);
    printElement("OWNER NAME", 20);
    printElement("DESCRIPTION", 50);
    printElement('\n', 0);
    printElement(regNumber, 10);
    Result<Person*> ownerResult = getOwner();
    if (ownerResult.isValid) {
        printElement(ownerResult.result->getName(), 20);
    }
    else {
        printElement("nullptr", 20);
    }
    printElement(description, 50);
}
