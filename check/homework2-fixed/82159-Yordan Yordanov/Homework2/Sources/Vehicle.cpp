
#include <stdexcept>

#include "../Headers/Vehicle.h"

Vehicle::Vehicle(const Registration &registration, const std::string &description)
        : registration(std::move(registration)), description(std::move(description)) {
    this->owner = nullptr;
}

Vehicle::Vehicle(const Vehicle &object) {
    this->registration = object.registration;
    this->description = object.description;
    this->owner = object.owner;
}

const std::string &Vehicle::getRegistration() const {
    return this->registration.getRegistration();
}

const std::string &Vehicle::getDescription() const {
    return this->description;
}

Person *Vehicle::getOwner() const {
    return (this->owner);
}

void Vehicle::setOwner(Person &owner) {
    if (this->owner != nullptr) {
        this->owner->removeVehicle(*this);
    }

    owner.addVehicle(*this);
    this->owner = &owner;
}


void Vehicle::removeOwner() {
    if (this->owner != nullptr) {
        this->owner->removeVehicle(*this);
        this->owner = nullptr;
    }
}

Vehicle &Vehicle::operator=(const Vehicle &object) {
    if (this != &object) {
        this->registration = object.registration;
        this->description = object.description;
        this->owner = nullptr;
        this->owner = object.owner;
    }

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Vehicle &object) {
    os << "Vehicle with: " << std::endl;
    os << object.registration;
    os << " Owner: ";
    if (object.owner != nullptr) {
        os << object.owner->getName() << std::endl;
    } else {
        os << "no one" << std::endl;
    }
    os << " Description: " << object.description << std::endl;

    return os;
}
