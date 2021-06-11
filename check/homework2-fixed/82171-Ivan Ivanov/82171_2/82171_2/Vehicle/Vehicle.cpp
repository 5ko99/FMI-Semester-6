#include "Vehicle.h"
#include "../Person/Person.h"

Vehicle::Vehicle(Registration registration, std::string description) : 
    registration(registration),
    description(description),
    owner(nullptr) {
        ;
}

Vehicle::Vehicle(const Vehicle& other) : 
    registration(other.registration),
    description(other.description),
    owner(other.owner) {
        ;
}

Vehicle* Vehicle::operator=(const Vehicle& other) {
    if(this == &other) {
        return this;
    }

    this->registration = other.registration;
    this->description = other.description;
    this->owner = other.owner;

    return this;
}

const Registration Vehicle::getRegistration() const {
    return this->registration;
}

Person* Vehicle::getOwner() const {
    return this->owner;
}

const std::string Vehicle::getDescription() const {
    return this->description;
}

void Vehicle::setOwner(Person* owner) {
    this->owner = owner;
}

void Vehicle::clearOwner() {
    if (!this->owner) {
        throw VehicleException("The vehicle has no owner!");
    }

    this->owner = nullptr;
}

Vehicle::~Vehicle() {
    ;
}

Vehicle* Vehicle::operator*() {
    return this;
}

std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle) {
    os << vehicle.registration <<  "\n" << vehicle.description << std::endl;
    return os;
}
